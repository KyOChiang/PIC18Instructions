/**
 * Author: Chiang Choon Yong
 * Email: yong931231@hotmail.com
 * Date: 07 - 04 - 2014
 * Project name: PIC18 simulator
 * Programme: Microelectronic with Embedded Technology
 * Institution: Tunku Abdul Rahman University College
 * Copyright: GPLv3
 */

#ifndef __BYTECODE_H__
#define __BYTECODE_H__

typedef enum {
				ACCESS = -5,
				BANKED,
				F,
				W
			 }Operand;
			 
typedef enum {
				ANDLW,
				XORLW,
				BNZ,
				CALL,
				NOP,
				MOVWF,
			    RLNCF,
			    SUBFWB,
				BTFSS,
				TBLRD_PREINC
} Mnemonic;

typedef enum {
				NO_ERROR,
				ERR_INVALID_OPERAND1,
				ERR_INVALID_OPERAND2,
				ERR_INVALID_OPERAND3,
				ERR_STKPTR_OVERFLOW,
				ERR_INVALID_BSR,
				ERR_NON_EMPTY_OPERAND,
			    ERR_INVALID_TBL_PTR
				
} ExceptionError;

typedef struct {
	Mnemonic mnemonic;
	char *name;
} Instruction;

typedef struct {
	Instruction instruction;
	long int operand1;
	int operand2;
	int operand3;
	long int absoluteAddress;
} Bytecode;

#endif // __BYTECODE_H__