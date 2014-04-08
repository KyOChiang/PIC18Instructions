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
#include "XORLW.h"

void setUp(){}
void tearDown(){}

void test_xorlw_with_invalid_operand1_negative1_should_throw_exception(){
	CEXCEPTION_T operandERR;
	
	//Test fixture
	//Initialize WREG with B5h and XOR with -1
	Bytecode code = {.instruction = {.mnemonic = XORLW, .name = "xorlw"},
					 .operand1 = -1,
					 .operand2 = -1,
					 .operand3 = -1,
					 .absoluteAddress = 0x01
					 };
	
	FSR[WREG] = 0xB5;
	Try{
		xorlw(&code);
	} Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1,operandERR);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xB5,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x01,code.absoluteAddress);

}

void test_xorlw_with_invalid_operand1_256_should_throw_exception(){
	CEXCEPTION_T operandERR;
	
	//Test fixture
	//Initialize WREG with B5h and XOR with 256
	Bytecode code = {.instruction = {.mnemonic = XORLW, .name = "xorlw"},
					 .operand1 = 256,
					 .operand2 = -1,
					 .operand3 = -1,
					 .absoluteAddress = 0x02
					 };
	
	FSR[WREG] = 0xB5;
	Try{
		xorlw(&code);
	} Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1,operandERR);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xB5,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x02,code.absoluteAddress);

}

void test_xorlw_with_valid_operand1_0x0A_should_xor_to_WREG_return_0xBF(){
	CEXCEPTION_T operandERR;
	
	//Test fixture
	//Initialize WREG with B5h and XOR with 0x0A
	Bytecode code = {.instruction = {.mnemonic = XORLW, .name = "xorlw"},
					 .operand1 = 0x0A,
					 .operand2 = -1,
					 .operand3 = -1,
					 .absoluteAddress = 0x03
					 };
	
	FSR[WREG] = 0xB5;
	//00001010 -> 0A
	//10110101 -> B5
	//10111111 -> BF
	
	Try{
		xorlw(&code);
	} Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1,operandERR);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xBF,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x04,code.absoluteAddress);
}

void test_xorlw_with_non_empty_operand2_0x00_should_throw_exception(){
	CEXCEPTION_T operandERR;
	
	//Test fixture
	//Initialize WREG with B5h and XOR with 0x0A
	//-1 represent empty
	Bytecode code = {.instruction = {.mnemonic = XORLW, .name = "xorlw"},
					 .operand1 = 0x0A,
					 .operand2 = 0,
					 .operand3 = -1,
					 .absoluteAddress = 0x04
					 };
	
	FSR[WREG] = 0xB5;
	//00001010 -> 0A
	//10110101 -> B5
	//10111111 -> BF
	
	Try{
		xorlw(&code);
	} Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND2,operandERR);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xB5,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x04,code.absoluteAddress);
}

void test_xorlw_with_non_empty_operand2_F_should_throw_exception(){
	CEXCEPTION_T operandERR;
	
	//Test fixture
	//Initialize WREG with B5h and XOR with 0x0A
	//-1 represent empty
	Bytecode code = {.instruction = {.mnemonic = XORLW, .name = "xorlw"},
					 .operand1 = 0x0A,
					 .operand2 = F,
					 .operand3 = -1,
					 .absoluteAddress = 0x05
					 };
	
	FSR[WREG] = 0xB5;
	//00001010 -> 0A
	//10110101 -> B5
	//10111111 -> BF
	
	Try{
		xorlw(&code);
	} Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND2,operandERR);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xB5,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x05,code.absoluteAddress);
}

void test_xorlw_with_non_empty_operand2_W_should_throw_exception(){
	CEXCEPTION_T operandERR;
	
	//Test fixture
	//Initialize WREG with B5h and XOR with 0x0A
	//-1 represent empty
	Bytecode code = {.instruction = {.mnemonic = XORLW, .name = "xorlw"},
					 .operand1 = 0x0A,
					 .operand2 = W,
					 .operand3 = -1,
					 .absoluteAddress = 0x07
					 };
	
	FSR[WREG] = 0xB5;
	//00001010 -> 0A
	//10110101 -> B5
	//10111111 -> BF
	
	Try{
		xorlw(&code);
	} Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND2,operandERR);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xB5,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x07,code.absoluteAddress);
}

void test_xorlw_with_non_empty_operand3_BANKED_should_throw_exception(){
	CEXCEPTION_T operandERR;
	
	//Test fixture
	//Initialize WREG with B5h and XOR with 0x0A
	Bytecode code = {.instruction = {.mnemonic = XORLW, .name = "xorlw"},
					 .operand1 = 0x0A,
					 .operand2 = -1,
					 .operand3 = BANKED,
					 .absoluteAddress = 0x09
					 };
	
	FSR[WREG] = 0xB5;
	//00001010 -> 0A
	//10110101 -> B5
	//10111111 -> BF
	
	Try{
		xorlw(&code);
	} Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND3,operandERR);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xB5,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x09,code.absoluteAddress);
}

void test_xorlw_with_non_empty_operand3_ACCESS_should_throw_exception(){
	CEXCEPTION_T operandERR;
	
	//Test fixture
	//Initialize WREG with B5h and XOR with 0x0A
	Bytecode code = {.instruction = {.mnemonic = XORLW, .name = "xorlw"},
					 .operand1 = 0x0A,
					 .operand2 = -1,
					 .operand3 = ACCESS,
					 .absoluteAddress = 0x0A
					 };
	
	FSR[WREG] = 0xB5;
	//00001010 -> 0A
	//10110101 -> B5
	//10111111 -> BF
	
	Try{
		xorlw(&code);
	} Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND3,operandERR);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xB5,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x0A,code.absoluteAddress);
}

void test_xorlw_with_valid_operand1_0xA5_should_xor_to_WREG_return_0xF0_and_set_the_neg_flag_in_STATUS_REG(){
	CEXCEPTION_T operandERR;
	
	//Test fixture
	//Initialize WREG with B5h and XOR with 0x0A
	Bytecode code = {.instruction = {.mnemonic = XORLW, .name = "xorlw"},
					 .operand1 = 0xA5,
					 .operand2 = -1,
					 .operand3 = -1,
					 .absoluteAddress = 0x0B
					 };
	
	FSR[WREG] = 0x55;
	//10100101 -> A5
	//01010101 -> 55
	//11110000 -> F0
	
	Try{
		xorlw(&code);
	} Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1,operandERR);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xF0,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x10,FSR[STATUS]);
	TEST_ASSERT_EQUAL_HEX8(0x0C,code.absoluteAddress);
}

void test_xorlw_with_valid_operand1_0xA5_should_xor_to_WREG_return_0x00_and_set_the_zero_flag_in_STATUS_REG(){
	CEXCEPTION_T operandERR;
	
	//Test fixture
	//Initialize WREG with A5h and XOR with 0x0A
	Bytecode code = {.instruction = {.mnemonic = XORLW, .name = "xorlw"},
					 .operand1 = 0xA5,
					 .operand2 = -1,
					 .operand3 = -1,
					 .absoluteAddress = 0x0C
					 };
	
	FSR[WREG] = 0xA5;
	//10100101 -> A5
	//10100101 -> A5
	//00000000 -> 00
	
	Try{
		xorlw(&code);
	} Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1,operandERR);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x04,FSR[STATUS]);
	TEST_ASSERT_EQUAL_HEX8(0x0D,code.absoluteAddress);
}

void test_xorlw_with_valid_operand1_0xA5_should_xor_to_WREG_return_0x20_and_do_not_set_any_flag_in_STATUS_REG(){
	CEXCEPTION_T operandERR;
	
	//Test fixture
	//Initialize WREG with A5h and XOR with 0x0A
	Bytecode code = {.instruction = {.mnemonic = XORLW, .name = "xorlw"},
					 .operand1 = 0xA5,
					 .operand2 = -1,
					 .operand3 = -1,
					 .absoluteAddress = 0x11
					 };
	
	FSR[WREG] = 0x85;
	//10100101 -> A5
	//10000101 -> 85
	//00100000 -> 20
	
	Try{
		xorlw(&code);
	} Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1,operandERR);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x20,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[STATUS]);
	TEST_ASSERT_EQUAL_HEX8(0x12,code.absoluteAddress);
}

