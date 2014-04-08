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
#include "CALL.h"

void setUp(){}
void tearDown(){}

void test_CALL_should_throw_exception_if_operand2_is_non_empty(){
	CEXCEPTION_T operandERR;
	
	Bytecode code = {.instruction = {.mnemonic = CALL, .name = "CALL"},
					 .operand1 = 0x256,
					 .operand2 = 2,
					 .operand3 = -1,
					 .absoluteAddress = 0x100
					 };				 
	Try{
		call(&code);
	}Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND2,operandERR);
	}
	
	TEST_ASSERT_EQUAL(0x100,code.absoluteAddress);
}

void test_CALL_should_throw_exception_if_operand3_is_non_empty(){
	CEXCEPTION_T operandERR;
	
	Bytecode code = {.instruction = {.mnemonic = CALL, .name = "CALL"},
					 .operand1 = 0x256,
					 .operand2 = -1,
					 .operand3 = 99,
					 .absoluteAddress = 0xAA
					 };				 
	Try{
		call(&code);
	}Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND3,operandERR);
	}
	
	TEST_ASSERT_EQUAL(0xAA,code.absoluteAddress);
}

void test_CALL_should_throw_exception_if_range_between_absoluteAddress_and_operand1_out_of_limit(){
	CEXCEPTION_T operandERR;
	
	Bytecode code = {.instruction = {.mnemonic = CALL, .name = "CALL"},
					 .operand1 = 0x8FFFFFFF,
					 .operand2 = -1,
					 .operand3 = -1,
					 .absoluteAddress = 0xAA
					 };				 
	Try{
		call(&code);
	}Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1,operandERR);
	}
	
	TEST_ASSERT_EQUAL(0xAA,code.absoluteAddress);
}

void test_CALL_should_go_to_0x5204_and_0xAC_will_push_to_TOS_and_STKPTR_increment_by1(){
	CEXCEPTION_T operandERR;
	
	Bytecode code = {.instruction = {.mnemonic = CALL, .name = "CALL"},
					 .operand1 = 0x5204,
					 .operand2 = -1,
					 .operand3 = -1,
					 .absoluteAddress = 0xAA
					 };	
	//Next two address from 0xAA - 0xAC
	FSR[STKPTR] = 0;
	FSR[TOSU] = 0x00;
	FSR[TOSH] = 0x00;
	FSR[TOSL] = 0x00;
	Try{
		call(&code);
	}Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1,operandERR);
	}
	TEST_ASSERT_EQUAL_HEX8(0x5204,code.absoluteAddress);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[TOSU]);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[TOSH]);
	TEST_ASSERT_EQUAL_HEX8(0xAC,FSR[TOSL]);
	TEST_ASSERT_EQUAL(1,FSR[STKPTR]);
}

void test_CALL_should_go_to_0xAC_and_0x5026_will_push_to_TOS_and_STKPTR_increment_by1(){
	CEXCEPTION_T operandERR;
	
	Bytecode code = {.instruction = {.mnemonic = CALL, .name = "CALL"},
					 .operand1 = 0xAC,
					 .operand2 = -1,
					 .operand3 = -1,
					 .absoluteAddress = 0x5024
					 };	
	//Next two address from 0x5024 - 0x5026
	FSR[STKPTR] = 1;
	FSR[TOSU] = 0x00;
	FSR[TOSH] = 0x00;
	FSR[TOSL] = 0xAC;
	Try{
		call(&code);
	}Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1,operandERR);
	}
	TEST_ASSERT_EQUAL_HEX8(0xAC,code.absoluteAddress);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[TOSU]);
	TEST_ASSERT_EQUAL_HEX8(0x50,FSR[TOSH]);
	TEST_ASSERT_EQUAL_HEX8(0x26,FSR[TOSL]);
	TEST_ASSERT_EQUAL(2,FSR[STKPTR]);
}

void test_CALL_should_throw_exception_if_STKPTR_overflow(){
	CEXCEPTION_T operandERR;
	
	Bytecode code = {.instruction = {.mnemonic = CALL, .name = "CALL"},
					 .operand1 = 0x8FFF,
					 .operand2 = -1,
					 .operand3 = -1,
					 .absoluteAddress = 0xAA
					 };	
	FSR[STKPTR] = 31;			 
	Try{
		call(&code);
	}Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_STKPTR_OVERFLOW,operandERR);
	}
	
	TEST_ASSERT_EQUAL(0xAA,code.absoluteAddress);
}