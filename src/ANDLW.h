/**
 * Author: Chiang Choon Yong
 * Email: yong931231@hotmail.com
 * Date: 07 - 04 - 2014
 * Project name: PIC18 simulator
 * Programme: Microelectronic with Embedded Technology
 * Institution: Tunku Abdul Rahman University College
 * Copyright: GPLv3
 */

#ifndef _ANDLW_H_
#define _ANDLW_H_

#define WREG 0xFE8
#define STATUS 0xFDB

extern char FSR[];

int andlw(Bytecode *code);

#endif