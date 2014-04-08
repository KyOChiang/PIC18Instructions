/**
 * Author: Chiang Choon Yong
 * Email: yong931231@hotmail.com
 * Date: 07 - 04 - 2014
 * Project name: PIC18 simulator
 * Programme: Microelectronic with Embedded Technology
 * Institution: Tunku Abdul Rahman University College
 * Copyright: GPLv3
 */

#include <stdio.h>
#include "CException.h"
#include "Bytecode.h"
#include "subfwb.h"

char FSR[0x1000];

int subfwb(Bytecode *code){

	char tempStore;
	char Carry;
	int tempOperand = code->operand1;
	
	if(FSR[BSR] < 0x00 || FSR[BSR] > 0x0F)
		Throw(ERR_INVALID_BSR);
		
	if(code->operand2 == BANKED||code->operand2 == ACCESS||code->operand2 == -4||code->operand2 == -5){
		if(code->operand3 == BANKED||code->operand3 == ACCESS||code->operand3 == -4||code->operand3 == -5)
			Throw(ERR_INVALID_OPERAND3);
	}
			
	if(code->operand2 == F||code->operand2 == W||code->operand2 == -2||code->operand2 == -3){
		if(code->operand3 == F||code->operand3 == W||code->operand3 == -2||code->operand3 == -3)
			Throw(ERR_INVALID_OPERAND2);
	}
	
	if(code->operand1 < 0)
		Throw(ERR_INVALID_OPERAND1);
		
	if((code->operand2 == BANKED)||(code->operand2 == ACCESS)){
		code->operand3 = code->operand3;
		code->operand2 = -1;
	}
	
	FSR[STATUS] = FSR[STATUS] & 0x01;
	if(FSR[STATUS] == 0x01)
		Carry = 0;
	else if(FSR[STATUS] == 0x00)
		Carry = 1;
	
	//SUBFWB operation on different range of FILE reg
	if((code->operand1 >= 0x80)&&(code->operand1 <= 0xF7F)){
		if((code->operand3 == ACCESS)||code->operand3 == 0)
			if(code->operand1 > 0xFF)
				Throw(ERR_INVALID_OPERAND1);
			else
				tempStore = FSR[WREG] - FSR[code->operand1+0xF00] - Carry;
		else{
			code->operand1 = (code->operand1 & 0xFF);
			tempStore = FSR[WREG] - FSR[code->operand1 + (FSR[BSR]<<8)] - Carry;
		}
	}
	else if((code->operand1 >= 0x00)&&(code->operand1 <= 0x7F)){
		tempStore = FSR[WREG] - FSR[code->operand1] - Carry;
	}
	else if((code->operand1 >= 0xF80)&&(code->operand1 <= 0xFFF)){
		tempStore =  FSR[WREG] - FSR[code->operand1] - Carry;
	}
	//printf("tempStore = %d\n",tempStore);	
	//Determine what is operand2 if empty
	if((code->operand3 == -1)||(code->operand3 == BANKED)){
		if(code->operand2 == -1)
			code->operand2 = F;
	}
	else if(code->operand3 == ACCESS){
		if(code->operand2 == -1)
			code->operand2 = W;
	}
	//printf("OP2 = %d\n",code->operand2);
	
	//Set NEGATIVE or ZERO flag based on tempStore
	if(tempStore == 0x00)
		FSR[STATUS] = 0x04;
	else if(tempStore < 0x00)
		FSR[STATUS] = 0x10;
	else
		FSR[STATUS] = 0x00;
	
	code->operand1 = tempOperand;
	//printf("OP1 = %d\n",code->operand1);
	//Determine where tempStore should store
	if((code->operand2 == F)||(code->operand2 == 1)){
		if((code->operand1 >= 0x80)&&(code->operand1 <= 0xF7F)){
			if((code->operand3 == ACCESS)||code->operand3 == 0)
				if(code->operand1 > 0xFF)
					Throw(ERR_INVALID_OPERAND1);
				else
					FSR[code->operand1+0xF00] = tempStore;
			else{
				code->operand1 = (code->operand1 & 0xFF);
				FSR[code->operand1 + (FSR[BSR]<<8)] = tempStore;
			}
		}
		else if((code->operand1 >= 0x00)&&(code->operand1 <= 0x7F))
			FSR[code->operand1] = tempStore;
		else if((code->operand1 >= 0xF80)&&(code->operand1 <= 0xFFF))
			FSR[code->operand1] = tempStore;
	}
	else if((code->operand2 == W)||(code->operand2 == 0))
		FSR[WREG] = tempStore;
	
	return (code->absoluteAddress = code->absoluteAddress + 1);
}