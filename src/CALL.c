/**
 * Author: Chiang Choon Yong
 * Email: yong931231@hotmail.com
 * Date: 07 - 04 - 2014
 * Project name: PIC18 simulator
 * Programme: Microelectronic with Embedded Technology
 * Institution: Tunku Abdul Rahman University College
 * Copyright: GPLv3
 */

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
#include "CALL.h"
#include "CException.h"

char FSR[0x1000];
long int PIC18Stack[32];


long int call(Bytecode *code) {
	int	tempBigger, tempSmaller;
	if(code->operand2 != -1){
		Throw(ERR_INVALID_OPERAND2);
	}
	if(code->operand3 != -1){
		Throw(ERR_INVALID_OPERAND3);
	}
	
	if(code->operand1>=code->absoluteAddress){
		tempBigger = code->operand1;
		tempSmaller = code->absoluteAddress;
	}
	else{
		tempSmaller = code->operand1;
		tempBigger = code->absoluteAddress;
	}
	
	if((tempBigger-tempSmaller>=0)&&(tempBigger-tempSmaller<=1048575)){
		
		FSR[TOSU] = ((code->absoluteAddress+2 & 0xFF0000)>>16);
		FSR[TOSH] = ((code->absoluteAddress+2 & 0x00FF00)>>8);
		FSR[TOSL] = (code->absoluteAddress+2 & 0x0000FF);
		
		FSR[STKPTR] = FSR[STKPTR] + 1;
		if(FSR[STKPTR]>31)
			Throw(ERR_STKPTR_OVERFLOW);
			
		return code->absoluteAddress = code->operand1;
	}
	else
		Throw(ERR_INVALID_OPERAND1);	
}