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
#include "BTFSS.h"

char FSR[0x1000];
int PC;

int btfss(Bytecode *code){
	int mask = 0x01;
	if(code->operand2 == -1||code->operand2 < 0||code->operand2 > 7){
		Throw(ERR_INVALID_OPERAND2);
	}
	if(code->operand3 == F||code->operand3 == W){
		Throw(ERR_INVALID_OPERAND3);
	}
	if(code->operand1 < 0x00||code->operand1 > 0xFF){
		Throw(ERR_INVALID_OPERAND1);
	}
	
	mask = mask<<(code->operand2);
	if(code->operand3 == BANKED || code->operand3 == -1){
		if((FSR[code->operand1+(FSR[BSR]<<8)] & mask)>>(code->operand2) == 1)
			return (code->absoluteAddress = code->absoluteAddress + 2);
		else
			return (code->absoluteAddress = code->absoluteAddress + 1);
	}
	else if(code->operand3 == ACCESS){
		if(code->operand1 >= 0x80){
			if((FSR[code->operand1+(0xF00)] & mask)>>(code->operand2) == 1)
				return (code->absoluteAddress = code->absoluteAddress + 2);
			else
				return (code->absoluteAddress = code->absoluteAddress + 1);
		}
		else if(code->operand1 < 0x80){
			//printf("%d",(FSR[code->operand1] & mask)>>code->operand2 );
			if((FSR[code->operand1] & mask)>>code->operand2 == 1)
				return (code->absoluteAddress = code->absoluteAddress + 2);
			else
				return (code->absoluteAddress = code->absoluteAddress + 2);
		}
	}
}