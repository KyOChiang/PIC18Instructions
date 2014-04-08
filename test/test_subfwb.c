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
#include "subfwb.h"

void setUp(){}
void tearDown(){}

void test_subfwb_should_throw_exception_if_operand2_and_operand3_have_same_value_ACCESS(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = SUBFWB, .name = "subfwb"},
					 .operand1 = 0x23,
					 .operand2 = ACCESS,
					 .operand3 = ACCESS,
					 .absoluteAddress = 0x05
					};
	FSR[code.operand1] = 0x45;
	FSR[WREG] = 0x50;
	
	Try{
		subfwb(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND3, errorStatus);
	}

	TEST_ASSERT_EQUAL_HEX8(0x45,FSR[code.operand1]);
	TEST_ASSERT_EQUAL_HEX8(0x50,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x05,code.absoluteAddress);
}

void test_subfwb_should_throw_exception_if_operand2_and_operand3_have_same_value_BANKED(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = SUBFWB, .name = "subfwb"},
					 .operand1 = 0x23,
					 .operand2 = BANKED,
					 .operand3 = BANKED,
					 .absoluteAddress = 0x05
					};
	FSR[code.operand1] = 0x45;
	FSR[WREG] = 0x50;
	
	Try{
		subfwb(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND3, errorStatus);
	}

	TEST_ASSERT_EQUAL_HEX8(0x45,FSR[code.operand1]);
	TEST_ASSERT_EQUAL_HEX8(0x50,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x05,code.absoluteAddress);
}

void test_subfwb_should_throw_exception_if_operand2_and_operand3_have_same_value_F(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = SUBFWB, .name = "subfwb"},
					 .operand1 = 0x50,
					 .operand2 = F,
					 .operand3 = F,
					 .absoluteAddress = 0x05
					};
	FSR[code.operand1] = 0x46;
	FSR[WREG] = 0x50;
	
	Try{
		subfwb(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND2, errorStatus);
	}

	TEST_ASSERT_EQUAL_HEX8(0x46,FSR[code.operand1]);
	TEST_ASSERT_EQUAL_HEX8(0x50,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x05,code.absoluteAddress);
}

void test_subfwb_should_throw_exception_if_operand2_and_operand3_have_same_value_W(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = SUBFWB, .name = "subfwb"},
					 .operand1 = 0x24,
					 .operand2 = W,
					 .operand3 = W,
					 .absoluteAddress = 0x05
					};
	FSR[code.operand1] = 0x66;
	FSR[WREG] = 0x50;
	
	Try{
		subfwb(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND2, errorStatus);
	}

	TEST_ASSERT_EQUAL_HEX8(0x66,FSR[code.operand1]);
	TEST_ASSERT_EQUAL_HEX8(0x50,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x05,code.absoluteAddress);
}

void test_subfwb_should_throw_exception_for_invalid_BSR(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = SUBFWB, .name = "subfwb"},
					 .operand1 = 0x88,
					 .operand2 = ACCESS,
					 .operand3 = ACCESS,
					 .absoluteAddress = 0x05
					};
	FSR[code.operand1] = 0x45;
	FSR[WREG] = 0x50;
	FSR[BSR] = 0xAA;
	
	Try{
		subfwb(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_BSR, errorStatus);
	}

	TEST_ASSERT_EQUAL_HEX8(0x45,FSR[code.operand1]);
	TEST_ASSERT_EQUAL_HEX8(0x50,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x05,code.absoluteAddress);
}

void test_subfwb_should_throw_exception_for_invalid_operand1_less_than_0(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = SUBFWB, .name = "subfwb"},
					 .operand1 = -22,
					 .operand2 = F,
					 .operand3 = ACCESS,
					 .absoluteAddress = 0xD5
					};
	FSR[code.operand1] = 0x45;
	FSR[WREG] = 0x50;
	FSR[BSR] = 0x01;
	
	Try{
		subfwb(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1, errorStatus);
	}

	TEST_ASSERT_EQUAL_HEX8(0x45,FSR[code.operand1]);
	TEST_ASSERT_EQUAL_HEX8(0x50,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0xD5,code.absoluteAddress);
}

void test_subfwb_should_subtract_file_reg_and_Carry_from_WREG_if_carry_flag_is_clear_and_store_in_file_reg(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = SUBFWB, .name = "subfwb"},
					 .operand1 = 0x69,
					 .operand2 = F,
					 .operand3 = ACCESS,
					 .absoluteAddress = 0xD6
					};
	
	// Carry is 1 if carry flag in STATUS register is clear
	// 0A-05-1(Carry) = 04
	FSR[code.operand1] = 0x05;
	FSR[WREG] = 0x0A;
	FSR[STATUS] = 0x00;
	
	Try{
		subfwb(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1, errorStatus);
	}

	TEST_ASSERT_EQUAL_HEX8(0x04,FSR[code.operand1]);
	TEST_ASSERT_EQUAL_HEX8(0x0A,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0xD7,code.absoluteAddress);
}

void test_subfwb_should_subtract_file_reg_and_Carry_from_WREG_if_carry_flag_is_set_and_store_in_WREG(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = SUBFWB, .name = "subfwb"},
					 .operand1 = 0x69,
					 .operand2 = W,
					 .operand3 = ACCESS,
					 .absoluteAddress = 0xA6
					};
	
	// Carry is 1 if carry flag in STATUS register is clear
	// 0A-05-1(Carry) = 04
	FSR[code.operand1] = 0x05;
	FSR[WREG] = 0x0A;
	FSR[STATUS] = 0x01;
	
	Try{
		subfwb(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1, errorStatus);
	}

	TEST_ASSERT_EQUAL_HEX8(0x05,FSR[code.operand1]);
	TEST_ASSERT_EQUAL_HEX8(0x05,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0xA7,code.absoluteAddress);
}

void test_subfwb_should_subtract_BANKED_file_reg_and_Carry_from_WREG_if_carry_flag_is_set_and_store_in_file_reg(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = SUBFWB, .name = "subfwb"},
					 .operand1 = 0x569,
					 .operand2 = F,
					 .operand3 = BANKED,
					 .absoluteAddress = 0xB6
					};
	
	// Carry is 1 if carry flag in STATUS register is clear
	// 0A-05-1(Carry) = 04
	FSR[code.operand1] = 0x04;
	FSR[WREG] = 0xDF;
	FSR[STATUS] = 0x01;
	FSR[BSR] = 0x05;
	
	Try{
		subfwb(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1, errorStatus);
	}
	TEST_ASSERT_EQUAL_HEX8(0xDB,FSR[code.operand1+ (FSR[BSR]<<8)]);
	TEST_ASSERT_EQUAL_HEX8(0xDF,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0xB7,code.absoluteAddress);
}
