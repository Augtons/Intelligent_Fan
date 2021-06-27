#ifndef _TIMER_H_
#define _TIMER_H_

#include "baseC51.h"

void Timer0_init();

void Timer0_setValue(u8 th, u8 tl);

void Timer0_enable(u8 enable);

void Timer0_intr_register(void (*intrFunc)());

u16 getTimer0Count();
//------------------------------//
void Timer1_init();

void Timer1_setValue(u8 th, u8 tl);

void Timer1_enable(u8 enable);

void Timer1_intr_register(void (*intrFunc)());

u16 getTimer1Count();

//----------------------------------//

void Timer2_init();

void Timer2_setValue(u8 th, u8 tl);

void Timer2_enable(u8 enable);

void Timer2_intr_register(void (*intrFunc)());

u16 getTimer2Count();

void Timer2_clearIntrState();

#endif