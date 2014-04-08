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
#include "BNZ.h"

char FSR[0x1000];
int PC;

int bnz(Bytecode *code){

	if((code->operand1 - code->absoluteAddress) > 127||(code->operand1 - code->absoluteAddress) < -128)
		Throw(ERR_INVALID_OPERAND1);
	if(code->operand2 != -1)
		Throw(ERR_INVALID_OPERAND2);
	if(code->operand3 != -1)
		Throw(ERR_INVALID_OPERAND3);
	
	if(FSR[STATUS] == 0x00){
		return code->absoluteAddress = code->operand1;
	}
	else if(FSR[STATUS] == 0x04){
		return (code->absoluteAddress = code->absoluteAddress + 1);
	}
	
	
	
}