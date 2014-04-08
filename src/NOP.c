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
#include "Bytecode.h"
#include "NOP.h"

char FSR[0x1000];


int nop(Bytecode *code){

	if(code->operand1 != -1){
		Throw(ERR_INVALID_OPERAND1);
	}
	if(code->operand2 != -1){
		Throw(ERR_INVALID_OPERAND2);
	}
	if(code->operand3 != -1){
		Throw(ERR_INVALID_OPERAND3);
	}
	
	
	return (code->absoluteAddress = code->absoluteAddress + 0x01);
}