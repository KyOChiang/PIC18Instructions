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
#include "rlncf.h"

void setUp(){}
void tearDown(){}

void test_rlncf_should_rotate_to_left_without_carry_with_valid_operand1(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x23,
					 .operand2 = -1,
					 .operand3 = -1,
					 .absoluteAddress = 0xAF
					};
					
	//Initialize FSR[code.operand1] with value 0xDC	- 1101 1100
	//After rotate to left, become 1011 1001 - B9
	FSR[code.operand1] = 0xDC;
	
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1, errorStatus);
	}

	TEST_ASSERT_EQUAL_HEX8(0xB9,FSR[code.operand1]);
	TEST_ASSERT_EQUAL_HEX8(0xB0,code.absoluteAddress);
	TEST_ASSERT_EQUAL_HEX8(0x10,FSR[STATUS]);

}

void test_rlncf_should_not_rotate_to_left_without_carry_with_invalid_operand1_negative1(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = -1,
					 .operand2 = -1,
					 .operand3 = -1,
					 .absoluteAddress = 0xAA
					};

	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1, errorStatus);
	}
	TEST_ASSERT_EQUAL_HEX8(0xAA,code.absoluteAddress);
}

void test_rlncf_should_rotate_to_left_without_carry_with_operand1_0x100(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x100,
					 .operand2 = -1,
					 .operand3 = -1,
					 .absoluteAddress = 0xAA
					};
	
	FSR[BSR] = 0x01;
	FSR[code.operand1] = 0xA5; //Before rotate : 10100101 After rotate : 01001011 0x4B
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1, errorStatus);
	}
	TEST_ASSERT_EQUAL_HEX8(0x4B,FSR[code.operand1+(FSR[BSR]<<8)]);
	TEST_ASSERT_EQUAL_HEX8(0xAB,code.absoluteAddress);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[STATUS]);
}

void test_rlncf_should_rotate_to_left_without_carry_and_store_inside_filereg(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x10,
					 .operand2 = F,
					 .operand3 = -1,
					 .absoluteAddress = 0x18
					};
					
	//Initialize FSR[code.operand1] with value 0xA4	- 1010 0100	
	//After rotate to left, become 0100 1001 - 49
	FSR[code.operand1] = 0x04;
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1, errorStatus);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x08,FSR[code.operand1]);
	TEST_ASSERT_EQUAL_HEX8(0x19,code.absoluteAddress);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[STATUS]);
}

void test_rlncf_should_rotate_to_left_without_carry_and_store_inside_WREG(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x10,
					 .operand2 = W,
					 .operand3 = -1,
					 .absoluteAddress = 0xCA
					};
					
	//Initialize FSR[code.operand1] with value 0xCB	- 1100 1011	
	//After rotate to left, become 1001 0111 - 0x97
	FSR[code.operand1] = 0xCB;
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1, errorStatus);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x97,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0xCB,code.absoluteAddress);
	TEST_ASSERT_EQUAL_HEX8(0x10,FSR[STATUS]);
}

void test_rlncf_should_not_rotate_to_left_without_carry_and_throw_exception_on_invalid_operand2_3_are_BANKED(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x10,
					 .operand2 = BANKED,
					 .operand3 = BANKED,
					 .absoluteAddress = 0xAC
					};
					
	//Initialize FSR[code.operand1] with value 0xA4	- 1010 0101	
	FSR[code.operand1] = 0xA5;
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND3, errorStatus);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xA5,FSR[code.operand1]);
	TEST_ASSERT_EQUAL_HEX8(0xAC,code.absoluteAddress);
}

void test_rlncf_should_not_rotate_to_left_without_carry_and_throw_exception_on_invalid_operand2_3_are_ACCESS(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x10,
					 .operand2 = ACCESS,
					 .operand3 = ACCESS,
					 .absoluteAddress = 0xDA
					};
					
	//Initialize FSR[code.operand1] with value 0xA4	- 1010 0101	
	FSR[code.operand1] = 0xA6;
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND3, errorStatus);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xA6,FSR[code.operand1]);
	TEST_ASSERT_EQUAL_HEX8(0xDA,code.absoluteAddress);
}

void test_rlncf_should_not_rotate_to_left_without_carry_and_throw_exception_on_invalid_operand2_3_are_ACCESS_BANKED(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x10,
					 .operand2 = ACCESS,
					 .operand3 = BANKED,
					 .absoluteAddress = 0xBB
					};
					
	//Initialize FSR[code.operand1] with value 0xA4	- 1010 0101	
	FSR[code.operand1] = 0xC5;
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND3, errorStatus);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xC5,FSR[code.operand1]);
	TEST_ASSERT_EQUAL_HEX8(0xBB,code.absoluteAddress);
}

void test_rlncf_should_not_rotate_to_left_without_carry_and_throw_exception_on_invalid_operand2_3_are_F(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x14,
					 .operand2 = F,
					 .operand3 = F,
					 .absoluteAddress = 0xAD
					};
					
	//Initialize FSR[code.operand1] with value 0xA4	- 1010 0101	
	FSR[code.operand1] = 0xA5;
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND2, errorStatus);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xA5,FSR[code.operand1]);
	TEST_ASSERT_EQUAL_HEX8(0xAD,code.absoluteAddress);
}

void test_rlncf_should_not_rotate_to_left_without_carry_and_throw_exception_on_invalid_operand2_3_are_W(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x1A,
					 .operand2 = W,
					 .operand3 = W,
					 .absoluteAddress = 0x96
					};
					
	//Initialize FSR[code.operand1] with value 0xA4	- 1010 0101	
	FSR[code.operand1] = 0xA5;
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND2, errorStatus);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xA5,FSR[code.operand1]);
	TEST_ASSERT_EQUAL_HEX8(0x96,code.absoluteAddress);
}

void test_rlncf_should_not_rotate_to_left_without_carry_and_throw_exception_on_invalid_operand2_3_are_W_F(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x13,
					 .operand2 = W,
					 .operand3 = F,
					 .absoluteAddress = 0x78
					};
					
	//Initialize FSR[code.operand1] with value 0xA4	- 1010 0101	
	FSR[code.operand1] = 0xA5;
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND2, errorStatus);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xA5,FSR[code.operand1]);
	TEST_ASSERT_EQUAL_HEX8(0x78,code.absoluteAddress);
}

void test_rlncf_should_rotate_to_left_without_carry_with_valid_operand1_and_operand2_is_ACCESS(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	//OP3 should be empty if OP2 is written as ACCESS OR BANKED
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x57,
					 .operand2 = ACCESS,
					 .operand3 = -1,
					 .absoluteAddress = 0x5D
					};
					
	//Initialize FSR[code.operand1] with value 0xCB	- 1100 1011	
	//After rotate to left, become 1001 0111 - 97
	FSR[code.operand1] = 0xCB;
	
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1, errorStatus);
	}

	TEST_ASSERT_EQUAL_HEX8(0x97,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x5E,code.absoluteAddress);
	TEST_ASSERT_EQUAL_HEX8(0x10,FSR[STATUS]);
}

void test_rlncf_should_rotate_to_left_without_carry_with_valid_operand1_and_operand2_is_BANKED(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	//OP3 should be empty if OP2 is written as ACCESS OR BANKED
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x59,
					 .operand2 = BANKED,
					 .operand3 = -1,
					 .absoluteAddress = 0xFA
					};
					
	//Initialize FSR[code.operand1] with value 0xBC	- 1011 1100
	//After rotate to left, become 0111 1001 - 79
	FSR[BSR] = 0x00;
	FSR[code.operand1] = 0xBC;
	
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1, errorStatus);
	}

	TEST_ASSERT_EQUAL_HEX8(0x79,FSR[code.operand1]);
	TEST_ASSERT_EQUAL_HEX8(0xFB,code.absoluteAddress);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[STATUS]);
}

void test_rlncf_should_not_rotate_to_left_without_carry_and_throw_exception_on_invalid_BSR(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x22,
					 .operand2 = F,
					 .operand3 = BANKED,
					 .absoluteAddress = 0xCA
					};
					
	//Initialize FSR[code.operand1] with value 0xA4	- 1010 0101	
	FSR[code.operand1] = 0xA8;
	FSR[BSR] = 0x10;
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_BSR, errorStatus);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xA8,FSR[code.operand1]);
	TEST_ASSERT_EQUAL_HEX8(0xCA,code.absoluteAddress);
}

void test_rlncf_should_rotate_to_left_without_carry_and_store_to_selected_BSR_FileREG(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x5FF,
					 .operand2 = F,
					 .operand3 = BANKED,
					 .absoluteAddress = 0x63
					};
					
	//Initialize FSR[code.operand1] with value 0x96	- 1001 0110
	//After rotate to left, become 0010 1101 - 2D
	FSR[code.operand1] = 0x96;
	FSR[BSR] = 0x05;
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_BSR, errorStatus);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x2D,FSR[code.operand1+(FSR[BSR]<<8)]);
	TEST_ASSERT_EQUAL_HEX8(0x64,code.absoluteAddress);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[STATUS]);
}

void test_rlncf_should_rotate_to_left_without_carry_and_store_to_WREG_without_consider_on_BSR(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x363,
					 .operand2 = W,
					 .operand3 = BANKED,
					 .absoluteAddress = 0x11
					};
					
	//Initialize FSR[code.operand1] with value 0x69	- 0110 1001
	//After rotate to left, become 1101 0010 - D2
	FSR[code.operand1] = 0x69;
	FSR[BSR] = 0x03;
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_BSR, errorStatus);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xD2,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x12,code.absoluteAddress);
	TEST_ASSERT_EQUAL_HEX8(0x10,FSR[STATUS]);
}

void test_rlncf_with_op1_more_than_0x7F_should_rotate_to_left_without_carry_and_store_to_BANKF_FileREG(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x89,
					 .operand2 = F,
					 .operand3 = ACCESS,
					 .absoluteAddress = 0x91
					};
					
	//Initialize FSR[code.operand1] with value 0x73	- 0111 0011
	//After rotate to left, become 1110 0110 - E6
	FSR[code.operand1+0xF00] = 0x73;
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_BSR, errorStatus);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xE6,FSR[code.operand1+0xF00]);
	TEST_ASSERT_EQUAL_HEX8(0x92,code.absoluteAddress);
	TEST_ASSERT_EQUAL_HEX8(0x10,FSR[STATUS]);
}

void test_rlncf_should_rotate_to_left_without_carry_and_set_the_negative_flag(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x23,
					 .operand2 = F,
					 .operand3 = BANKED,
					 .absoluteAddress = 0x98
					};
					
	//Initialize FSR[code.operand1] with value 0x45	- 0100 0101	
	//After rotate to left, become 1000 1010 - 8A
	FSR[code.operand1] = 0x45;
	FSR[BSR] = 0x00;
	
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1, errorStatus);
	}

	TEST_ASSERT_EQUAL_HEX8(0x8A,FSR[code.operand1]);
	TEST_ASSERT_EQUAL_HEX8(0x99,code.absoluteAddress);
	TEST_ASSERT_EQUAL_HEX8(0x10,FSR[STATUS]);

}

void test_rlncf_should_rotate_to_left_without_carry_and_set_the_zero_flag(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x18,
					 .operand2 = F,
					 .operand3 = BANKED,
					 .absoluteAddress = 0x120
					};
					
	FSR[code.operand1] = 0x00;
	FSR[BSR] = 0x00;
	
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1, errorStatus);
	}

	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[code.operand1]);
	TEST_ASSERT_EQUAL_HEX8(0x121,code.absoluteAddress);
	TEST_ASSERT_EQUAL_HEX8(0x04,FSR[STATUS]);

}