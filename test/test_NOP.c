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
#include "NOP.h"

void setUp(){}
void tearDown(){}

void test_nop_should_do_nothing_and_return_0(){
	CEXCEPTION_T operandERR;
	
	Bytecode code = {.instruction = {.mnemonic = NOP, .name = "nop"},
					 .operand1 = -1,
					 .operand2 = -1,
					 .operand3 = -1,
					 .absoluteAddress = 0x00
					 };
					 
	Try{
		nop(&code);
	}Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1,operandERR);
	}
	TEST_ASSERT_EQUAL_HEX8(0x01, code.absoluteAddress);
}

void test_nop_should_do_nothing_but_throw_exception_for_invalid_operand1(){
	CEXCEPTION_T operandERR;
	Bytecode code = {.instruction = {.mnemonic = NOP, .name = "nop"},
					 .operand1 = 123,
					 .operand2 = -1,
					 .operand3 = -1,
					 .absoluteAddress = 0x00
					 };
	Try{
		nop(&code);
	}Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1,operandERR);
	}
	TEST_ASSERT_EQUAL_HEX8(0x00, code.absoluteAddress);
}
void test_nop_should_do_nothing_but_throw_exception_for_invalid_operand2(){
	CEXCEPTION_T operandERR;
	Bytecode code = {.instruction = {.mnemonic = NOP, .name = "nop"},
					 .operand1 = -1,
					 .operand2 = 321,
					 .operand3 = -1,
					 .absoluteAddress = 0x00
					 };
					 
	Try{
		nop(&code);
	}Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND2,operandERR);
	}
	TEST_ASSERT_EQUAL_HEX8(0x00, code.absoluteAddress);
}

void test_nop_should_do_nothing_but_throw_exception_for_invalid_operand3(){
	CEXCEPTION_T operandERR;
	Bytecode code = {.instruction = {.mnemonic = NOP, .name = "nop"},
					 .operand1 = -1,
					 .operand2 = -1,
					 .operand3 = 456,
					 .absoluteAddress = 0x00
					 };
					 
	Try{
		nop(&code);
	}Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND3,operandERR);
	}
	TEST_ASSERT_EQUAL_HEX8(0x00, code.absoluteAddress);
}
