/**
 * Author: Chiang Choon Yong
 * Email: yong931231@hotmail.com
 * Date: 07 - 04 - 2014
 * Project name: PIC18 simulator
 * Programme: Microelectronic with Embedded Technology
 * Institution: Tunku Abdul Rahman University College
 * Copyright: GPLv3
 */

#ifndef _CALL_H_
#define _CALL_H_

#define WREG 0xFE8
#define TOSU 0xFFF
#define TOSH 0xFFE
#define TOSL 0xFFD
#define STKPTR 0xFFC

extern char FSR[];
extern long int PIC18Stack[];

long int call(Bytecode *code);

#endif