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
#include "BTFSS.h"

void setUp(){}
void tearDown(){}

void test_btfss_should_not_check_bit_and_throw_exception_with_invalid_operand1_is_0x256(){
	CEXCEPTION_T operandERR;
	
	Bytecode code = {.instruction = {.mnemonic = BTFSS, .name = "btfss"},
					 .operand1 = 0x256,
					 .operand2 = 0,
					 .operand3 = -1,
					 .absoluteAddress = 0x00
					 };				 
	Try{
		btfss(&code);
	}Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1,operandERR);
	}
	TEST_ASSERT_EQUAL_HEX8(0x00,code.absoluteAddress);
}

void test_btfss_should_not_check_bit_and_throw_exception_with_invalid_operand1_is_neg_200(){
	CEXCEPTION_T operandERR;
	
	Bytecode code = {.instruction = {.mnemonic = BTFSS, .name = "btfss"},
					 .operand1 = -200,
					 .operand2 = 0,
					 .operand3 = -1,
					 .absoluteAddress = 0x00
					 };				 
	Try{
		btfss(&code);
	}Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1,operandERR);
	}
	TEST_ASSERT_EQUAL_HEX8(0x00,code.absoluteAddress);
}

void test_btfss_should_not_check_bit_and_throw_exception_with_invalid_operand2_is_8(){
	CEXCEPTION_T operandERR;
	
	Bytecode code = {.instruction = {.mnemonic = BTFSS, .name = "btfss"},
					 .operand1 = 123,
					 .operand2 = 8,
					 .operand3 = -1,
					 .absoluteAddress = 0x00
					 };				 
	Try{
		btfss(&code);
	}Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND2,operandERR);
	}
	TEST_ASSERT_EQUAL_HEX8(0x00,code.absoluteAddress);
}

void test_btfss_should_not_check_bit_and_throw_exception_with_invalid_operand2_is_neg20(){
	CEXCEPTION_T operandERR;
	
	Bytecode code = {.instruction = {.mnemonic = BTFSS, .name = "btfss"},
					 .operand1 = 123,
					 .operand2 = -20,
					 .operand3 = -1,
					 .absoluteAddress = 0x00
					 };				 
	Try{
		btfss(&code);
	}Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND2,operandERR);
	}
	TEST_ASSERT_EQUAL_HEX8(0x00,code.absoluteAddress);
}

void test_btfss_should_not_check_bit_and_throw_exception_with_invalid_operand2_is_F(){
	CEXCEPTION_T operandERR;
	
	Bytecode code = {.instruction = {.mnemonic = BTFSS, .name = "btfss"},
					 .operand1 = 123,
					 .operand2 = F,
					 .operand3 = -1,
					 .absoluteAddress = 0x00
					 };				 
	Try{
		btfss(&code);
	}Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND2,operandERR);
	}
	TEST_ASSERT_EQUAL_HEX8(0x00,code.absoluteAddress);
}

void test_btfss_should_not_check_bit_and_throw_exception_with_invalid_operand2_is_W(){
	CEXCEPTION_T operandERR;
	
	Bytecode code = {.instruction = {.mnemonic = BTFSS, .name = "btfss"},
					 .operand1 = 123,
					 .operand2 = W,
					 .operand3 = -1,
					 .absoluteAddress = 0x00
					 };				 
	Try{
		btfss(&code);
	}Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND2,operandERR);
	}
	TEST_ASSERT_EQUAL_HEX8(0x00,code.absoluteAddress);
}

void test_btfss_should_not_check_bit_and_throw_exception_with_invalid_operand3_is_F(){
	CEXCEPTION_T operandERR;
	
	Bytecode code = {.instruction = {.mnemonic = BTFSS, .name = "btfss"},
					 .operand1 = 123,
					 .operand2 = 7,
					 .operand3 = F,
					 .absoluteAddress = 0x00
					 };				 
	Try{
		btfss(&code);
	}Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND3,operandERR);
	}
	TEST_ASSERT_EQUAL_HEX8(0x00,code.absoluteAddress);
}

void test_btfss_should_not_check_bit_and_throw_exception_with_invalid_operand3_is_W(){
	CEXCEPTION_T operandERR;
	
	Bytecode code = {.instruction = {.mnemonic = BTFSS, .name = "btfss"},
					 .operand1 = 123,
					 .operand2 = 7,
					 .operand3 = W,
					 .absoluteAddress = 0x00
					 };				 
	Try{
		btfss(&code);
	}Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND3,operandERR);
	}
	TEST_ASSERT_EQUAL_HEX8(0x00,code.absoluteAddress);
}

void test_btfss_should_not_skip_if_there_is_0_is_check_bit_location(){
	CEXCEPTION_T operandERR;
	
	Bytecode code = {.instruction = {.mnemonic = BTFSS, .name = "btfss"},
					 .operand1 = 0x12,
					 .operand2 = 7,
					 .operand3 = -1,
					 .absoluteAddress = 0x22
					 };			
	FSR[BSR] = 0x00;
	FSR[code.operand1] = 0x7D; // 0111 1101
	
	Try{
		btfss(&code);
	}Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1,operandERR);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x23,code.absoluteAddress);
}

void test_btfss_should_skip_if_there_is_1_is_check_bit_location(){
	CEXCEPTION_T operandERR;
	
	Bytecode code = {.instruction = {.mnemonic = BTFSS, .name = "btfss"},
					 .operand1 = 0x12,
					 .operand2 = 5,
					 .operand3 = -1,
					 .absoluteAddress = 0x22
					 };			
	FSR[BSR] = 0x00;
	FSR[code.operand1] = 0x7D;
	
	Try{
		btfss(&code);
	}Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1,operandERR);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x24,code.absoluteAddress);
}

void test_btfss_should_skip_if_there_is_1_is_bit_0_location(){
	CEXCEPTION_T operandERR;
	
	Bytecode code = {.instruction = {.mnemonic = BTFSS, .name = "btfss"},
					 .operand1 = 0x12,
					 .operand2 = 0,
					 .operand3 = -1,
					 .absoluteAddress = 0x36
					 };			
	FSR[BSR] = 0x00;
	FSR[code.operand1] = 0x7D;
	
	Try{
		btfss(&code);
	}Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1,operandERR);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x38,code.absoluteAddress);
}

void test_btfss_should_not_skip_if_there_is_0_is_bit_1_location(){
	CEXCEPTION_T operandERR;
	
	Bytecode code = {.instruction = {.mnemonic = BTFSS, .name = "btfss"},
					 .operand1 = 0x12,
					 .operand2 = 1,
					 .operand3 = -1,
					 .absoluteAddress = 0x3A
					 };			
	
	FSR[BSR] = 0x00;
	FSR[code.operand1] = 0x7D;
	
	Try{
		btfss(&code);
	}Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1,operandERR);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x3B,code.absoluteAddress);
}







