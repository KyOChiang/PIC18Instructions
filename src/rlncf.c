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
#include "rlncf.h"

char FSR[0x1000];


/*  Before rlncf: file reg [7]-[6]-[5]-[4]-[3]-[2]-[1]-[0]
 *    
 *	After rlncf: file reg [6]-[5]-[4]-[3]-[2]-[1]-[0]-[7]
 *
 *	Again rlncf: file reg [5]-[4]-[3]-[2]-[1]-[0]-[7]-[6]
 */

int rlncf(Bytecode *code){

	char tempRotate = 0;
	char tempStore;
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
		
	//Check D7 is 1 or not
	if(FSR[code->operand1]<0)
		tempRotate = 0x01;
	else
		tempRotate = 0x00;
		
	//RLNCF operation on different range of FILE reg
	if((code->operand1 >= 0x80)&&(code->operand1 <= 0xF7F)){
		if((code->operand3 == ACCESS)||code->operand3 == 0)
			if(code->operand1 > 0xFF)
				Throw(ERR_INVALID_OPERAND1);
			else
				tempStore = FSR[code->operand1+0xF00]<<1;
		else{
			code->operand1 = (code->operand1 & 0xFF);
			tempStore = FSR[code->operand1 + (FSR[BSR]<<8)]<<1;
		}
		tempStore = tempStore + tempRotate;
	}
	else if((code->operand1 >= 0x00)&&(code->operand1 <= 0x7F)){
		tempStore = FSR[code->operand1]<<1;
		tempStore = tempStore + tempRotate;
	}
	else if((code->operand1 >= 0xF80)&&(code->operand1 <= 0xFFF)){
		tempStore = FSR[code->operand1]<<1;
		tempStore = tempStore + tempRotate;
	}

	//Determine what is operand2 if empty
	if((code->operand3 == -1)||(code->operand3 == BANKED)){
		if(code->operand2 == -1)
			code->operand2 = F;
	}
	else if(code->operand3 == ACCESS){
		if(code->operand2 == -1)
			code->operand2 = W;
	}

	//Set NEGATIVE or ZERO flag based on tempStore
	if(tempStore == 0x00)
		FSR[STATUS] = 0x04;
	else if(tempStore < 0x00)
		FSR[STATUS] = 0x10;
	else
		FSR[STATUS] = 0x00;
	
	code->operand1 = tempOperand;

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
	
	return code->absoluteAddress = code->absoluteAddress + 1;
}