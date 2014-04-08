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
#include "ANDLW.h"

void setUp(){}
void tearDown(){}

void test_andlw_with_invalid_operand1_negative1_should_throw_exception(){
	CEXCEPTION_T operandERR;
	
	//Test fixture
	//Initialize WREG with B5h and AND with -1
	Bytecode code = {.instruction = {.mnemonic = ANDLW, .name = "andlw"},
					 .operand1 = -1,
					 .operand2 = -1,
					 .operand3 = -1,
					 .absoluteAddress = 0x100
					 };
	
	FSR[WREG] = 0xB5;
	Try{
		andlw(&code);
	} Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1,operandERR);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xB5,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x100,code.absoluteAddress);
}

void test_andlw_with_invalid_operand1_256_should_throw_exception(){
	CEXCEPTION_T operandERR;
	
	//Test fixture
	//Initialize WREG with B5h and AND with 256
	Bytecode code = {.instruction = {.mnemonic = ANDLW, .name = "andlw"},
					 .operand1 = 256,
					 .operand2 = -1,
					 .operand3 = -1,
					 .absoluteAddress = 0x120
					 };
	
	FSR[WREG] = 0xB5;
	Try{
		andlw(&code);
	} Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1,operandERR);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xB5,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x120,code.absoluteAddress);
}

void test_andlw_with_valid_operand1_0x5A_should_xor_to_WREG_return_0x10(){
	CEXCEPTION_T operandERR;
	
	//Test fixture
	//Initialize WREG with B5h and AND with 0x0A
	Bytecode code = {.instruction = {.mnemonic = ANDLW, .name = "andlw"},
					 .operand1 = 0x5A,
					 .operand2 = -1,
					 .operand3 = -1,
					 .absoluteAddress = 0x100
					 };
	
	FSR[WREG] = 0xB5;
	//01011010 -> 5A
	//10110101 -> B5
	//00010000 -> 10
	
	Try{
		andlw(&code);
	} Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1,operandERR);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x10,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x101,code.absoluteAddress);
}

void test_andlw_with_non_empty_operand2_0x00_should_throw_exception(){
	CEXCEPTION_T operandERR;
	
	//Test fixture
	//-1 represent empty
	Bytecode code = {.instruction = {.mnemonic = ANDLW, .name = "andlw"},
					 .operand1 = 0x0A,
					 .operand2 = 0,
					 .operand3 = -1,
					 .absoluteAddress = 0x11
					 };
	
	FSR[WREG] = 0xB5;
	Try{
		andlw(&code);
	} Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND2,operandERR);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xB5,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x11,code.absoluteAddress);
}

void test_andlw_with_non_empty_operand2_F_should_throw_exception(){
	CEXCEPTION_T operandERR;

	Bytecode code = {.instruction = {.mnemonic = ANDLW, .name = "andlw"},
					 .operand1 = 0x0A,
					 .operand2 = F,
					 .operand3 = -1,
					 .absoluteAddress = 0x11
					 };
	
	FSR[WREG] = 0xB5;

	
	Try{
		andlw(&code);
	} Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND2,operandERR);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xB5,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x11,code.absoluteAddress);
}

void test_andlw_with_non_empty_operand2_W_should_throw_exception(){
	CEXCEPTION_T operandERR;
	
	Bytecode code = {.instruction = {.mnemonic = ANDLW, .name = "andlw"},
					 .operand1 = 0x0A,
					 .operand2 = W,
					 .operand3 = -1,
					 .absoluteAddress = 0x13
					 };
	
	FSR[WREG] = 0xB5;

	Try{
		andlw(&code);
	} Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND2,operandERR);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xB5,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x13,code.absoluteAddress);

}

void test_andlw_with_non_empty_operand3_BANKED_should_throw_exception(){
	CEXCEPTION_T operandERR;
	
	Bytecode code = {.instruction = {.mnemonic = ANDLW, .name = "andlw"},
					 .operand1 = 0x0A,
					 .operand2 = -1,
					 .operand3 = BANKED,
					 .absoluteAddress = 0x16
					 };
	
	FSR[WREG] = 0xB5;
	
	Try{
		andlw(&code);
	} Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND3,operandERR);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xB5,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x16,code.absoluteAddress);
}

void test_andlw_with_non_empty_operand3_ACCESS_should_throw_exception(){
	CEXCEPTION_T operandERR;
	
	Bytecode code = {.instruction = {.mnemonic = ANDLW, .name = "andlw"},
					 .operand1 = 0x0A,
					 .operand2 = -1,
					 .operand3 = ACCESS,
					 .absoluteAddress = 0x15
					 };
	
	FSR[WREG] = 0xB5;
	
	Try{
		andlw(&code);
	} Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND3,operandERR);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xB5,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x15,code.absoluteAddress);
}

void test_andlw_with_valid_operand1_0xCD_should_and_to_WREG_return_0x85_and_set_the_neg_flag_in_STATUS_REG(){
	CEXCEPTION_T operandERR;
	
	Bytecode code = {.instruction = {.mnemonic = ANDLW, .name = "andlw"},
					 .operand1 = 0xCD,
					 .operand2 = -1,
					 .operand3 = -1,
					 .absoluteAddress = 0x18
					 };
	
	FSR[WREG] = 0x85;
	//11001101 -> CD
	//10000101 -> 85
	//10000101 -> 85
	
	Try{
		andlw(&code);
	} Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1,operandERR);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x85,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x10,FSR[STATUS]);
	TEST_ASSERT_EQUAL_HEX8(0x19,code.absoluteAddress);
}

void test_andlw_with_valid_operand1_0xAA_should_xor_to_WREG_return_0x00_and_set_the_zero_flag_in_STATUS_REG(){
	CEXCEPTION_T operandERR;
	
	Bytecode code = {.instruction = {.mnemonic = ANDLW, .name = "andlw"},
					 .operand1 = 0xAA,
					 .operand2 = -1,
					 .operand3 = -1,
					 .absoluteAddress = 0x90
					 };
	
	FSR[WREG] = 0x00;
	//10101010 -> AA
	//00000000 -> 00
	//00000000 -> 00
	
	Try{
		andlw(&code);
	} Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1,operandERR);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x04,FSR[STATUS]);
	TEST_ASSERT_EQUAL_HEX8(0x91,code.absoluteAddress);
}

void test_andlw_with_valid_operand1_0xA5_should_xor_to_WREG_return_0x05_and_do_not_set_any_flag_in_STATUS_REG(){
	CEXCEPTION_T operandERR;

	Bytecode code = {.instruction = {.mnemonic = ANDLW, .name = "andlw"},
					 .operand1 = 0xA5,
					 .operand2 = -1,
					 .operand3 = -1,
					 .absoluteAddress = 0x34
					 };
	
	FSR[WREG] = 0x55;
	//10100101 -> A5
	//01010101 -> 55
	//00000101 -> 05
	
	Try{
		andlw(&code);
	} Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1,operandERR);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x05,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[STATUS]);
	TEST_ASSERT_EQUAL_HEX8(0x35,code.absoluteAddress);

}
