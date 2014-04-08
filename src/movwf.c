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
#include "movwf.h"

char FSR[0x1000];

int movwf(Bytecode *code){

	if(FSR[BSR] < 0x00 || FSR[BSR] > 0x0F)
		Throw(ERR_INVALID_BSR);
	if((code->operand2 == F)||(code->operand2 == W))
		Throw(ERR_INVALID_OPERAND2);
	if((code->operand2 == ACCESS)||(code->operand2 == BANKED)||(code->operand2 == 0)||(code->operand2 == 1)){
		if((code->operand3 == ACCESS)||(code->operand3 == BANKED)||(code->operand3 == 1)||(code->operand3 == 0)){
			Throw(ERR_INVALID_OPERAND3);
		}
	}
	
	if(code->operand3 == -1){
		if((code->operand1 >= 0x80)&&(code->operand1 <= 0x7F7)){
			code->operand1 = (code->operand1 & 0xFF);
			FSR[code->operand1 + (FSR[BSR]<<8)] = FSR[WREG];
		}
		else if((code->operand1 >= 0x00)&&(code->operand1 <= 0x7F))
			FSR[code->operand1] = FSR[WREG];
		else if((code->operand1 >= 0xF80)&&(code->operand1 <= 0xFFF))
			FSR[code->operand1] = FSR[WREG];
	}
	else if(code->operand3 == BANKED){
		code->operand1 = (code->operand1 & 0xFF);
		FSR[code->operand1 + (FSR[BSR]<<8)] = FSR[WREG];
	}
	else if(code->operand3 == ACCESS){
		code->operand1 = (code->operand1 & 0xFF);
		if((code->operand1 >= 0x00)&&(code->operand1 <= 0x7F))
			FSR[code->operand1] = FSR[WREG];
		else if((code->operand1 >= 0x80)&&(code->operand1 <= 0xFF))
			FSR[code->operand1+0xF00] = FSR[WREG];
	}	
		
	return (code->absoluteAddress = code->absoluteAddress + 1);
}