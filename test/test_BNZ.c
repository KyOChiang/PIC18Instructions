/**
 * Author: Chiang Choon Yong
 * Email: yong931231@hotmail.com
 * Date: 07 - 04 - 2014
 * Project name: PIC18 simulator
 * Programme: Microelectronic with Embedded Technology
 * Institution: Tunku Abdul Rahman University College
 * Copyright: GPLv3
 */

#include "unity.h"
#include "CException.h"
#include "Bytecode.h"
#include "BNZ.h"

void setUp(){}
void tearDown(){}

void test_bnz_should_not_branch_throw_exception_if_operand1_is_invalid_by_exceeding_127(){
	CEXCEPTION_T operandERR;
	
	Bytecode code = {.instruction = {.mnemonic = BNZ, .name = "bnz"},
					 .operand1 = 0x256,
					 .operand2 = -1,
					 .operand3 = -1,
					 .absoluteAddress = 0x100
					 };				 
	Try{
		bnz(&code);
	}Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1,operandERR);
	}
	
	TEST_ASSERT_EQUAL(0x100,code.absoluteAddress);
}

void test_bnz_should_not_branch_and_throw_exception_if_operand1_is_invalid_that_less_than_neg_128(){
	CEXCEPTION_T operandERR;
	
	Bytecode code = {.instruction = {.mnemonic = BNZ, .name = "bnz"},
					 .operand1 = 0x100,
					 .operand2 = -1,
					 .operand3 = -1,
					 .absoluteAddress = 0x256
					 };				 
	Try{
		bnz(&code);
	}Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1,operandERR);
	}
	
	TEST_ASSERT_EQUAL(0x256, code.absoluteAddress);
}

void test_bnz_should_not_branch_and_throw_exception_if_operand2_is_invalid(){
	CEXCEPTION_T operandERR;
	
	Bytecode code = {.instruction = {.mnemonic = BNZ, .name = "bnz"},
					 .operand1 = 0x255,
					 .operand2 = F,
					 .operand3 = -1,
					 .absoluteAddress = 0x256
					 };			 
	Try{
		bnz(&code);
	}Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND2,operandERR);
	}
	
	TEST_ASSERT_EQUAL(0x256, code.absoluteAddress);
}

void test_bnz_should_not_branch_and_throw_exception_if_operand3_is_invalid(){
	CEXCEPTION_T operandERR;
	
	Bytecode code = {.instruction = {.mnemonic = BNZ, .name = "bnz"},
					 .operand1 = 0x287,
					 .operand2 = -1,
					 .operand3 = BANKED,
					 .absoluteAddress = 0x256
					 };
			 
	Try{
		bnz(&code);
	}Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND3,operandERR);
	}
	
	TEST_ASSERT_EQUAL(0x256, code.absoluteAddress);
}

void test_bnz_should_branch_and_if_zero_flag_in_STATUS_REG_is_clear(){
	CEXCEPTION_T operandERR;
	
	Bytecode code = {.instruction = {.mnemonic = BNZ, .name = "bnz"},
					 .operand1 = 0x1C8,
					 .operand2 = -1,
					 .operand3 = -1,
					 .absoluteAddress = 0x246
					 };
	FSR[STATUS] = 0x00;	
	Try{
		bnz(&code);
	}Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1,operandERR);
	}
	
	TEST_ASSERT_EQUAL(code.operand1,code.absoluteAddress);
}

void test_bnz_should_not_branch_and_if_zero_flag_in_STATUS_REG_is_set(){
	CEXCEPTION_T operandERR;
	
	Bytecode code = {.instruction = {.mnemonic = BNZ, .name = "bnz"},
					 .operand1 = 0x2D3,
					 .operand2 = -1,
					 .operand3 = -1,
					 .absoluteAddress = 0x267
					 };
	FSR[STATUS] = 0x04;	
	Try{
		bnz(&code);
	}Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1,operandERR);
	}
	
	TEST_ASSERT_EQUAL(0x268, code.absoluteAddress);
}

