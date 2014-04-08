/**
 * Author: Chiang Choon Yong
 * Email: yong931231@hotmail.com
 * Date: 07 - 04 - 2014
 * Project name: PIC18 simulator
 * Programme: Microelectronic with Embedded Technology
 * Institution: Tunku Abdul Rahman University College
 * Copyright: GPLv3
 */

#ifndef _SUBFWB_H_
#define _SUBFWB_H_

extern char FSR[];

#define WREG 0xFE8
#define BSR 0xFE0
#define STATUS 0xFD8

int subfwb(Bytecode *code);

#endif // _SUBFWB_H_