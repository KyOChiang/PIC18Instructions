/**
 * Author: Chiang Choon Yong
 * Email: yong931231@hotmail.com
 * Date: 07 - 04 - 2014
 * Project name: PIC18 simulator
 * Programme: Microelectronic with Embedded Technology
 * Institution: Tunku Abdul Rahman University College
 * Copyright: GPLv3
 */

#ifndef _BTFSS_H_
#define _BTFSS_H_

#define WREG 0xFE8
#define STATUS 0xFD8
#define BSR 0xFE0

extern char FSR[];

int btfss(Bytecode *code);

#endif