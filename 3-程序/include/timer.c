#include "timer.h"

static void (*intrFunctionT0)();
static void (*intrFunctionT1)();
static void (*intrFunctionT2)();

void Timer0_init(){
    TMOD |= 0x01;
    EA = 1;
    ET0 = 1;
}

void Timer0_setValue(u8 th, u8 tl){
    TH0 = th;
    TL0 = tl;
}

void Timer0_enable(u8 enable){
    TR0 = enable;
}

void Timer0_intr_register(void (*intrFunc)()){
    intrFunctionT0 = intrFunc;
}

void Timer0_intr() interrupt 1{
    intrFunctionT0();
}

u16 getTimer0Count(){
    u16 temp = 0x00;
    TR0 = 0;
    temp = (0x00 | TH0) << 8;
    return temp | TL0;
}
//------------------------------//
void Timer1_init(){
    TMOD |= 0x10;
    EA = 1;
    ET1 = 1;
}

void Timer1_setValue(u8 th, u8 tl){
    TH1 = th;
    TL1 = tl;
}

void Timer1_enable(u8 enable){
    TR1 = enable;
}

void Timer1_intr_register(void (*intrFunc)()){
    intrFunctionT1 = intrFunc;
}

void Timer1_intr() interrupt 3{
    intrFunctionT1();
}

u16 getTimer1Count(){
    u16 temp = 0x00;
    TR1 = 0;
    temp = (0x00 | TH1) << 8;
    return temp | TL1;
}

//---------------------------------//

void Timer2_init(){
    T2CON = 0x00;
    ET2 = 1;
    EA = 1;
}

void Timer2_setValue(u8 th, u8 tl){
    RCAP2H = TH2 = th;
    RCAP2L = TL2 = tl;
}

void Timer2_enable(u8 enable){
    TR2 = enable;
}

void Timer2_intr_register(void (*intrFunc)()){
    intrFunctionT2 = intrFunc;
}

void Timer2_intr() interrupt 5{
    intrFunctionT2();
}

u16 getTimer2Count(){
    u16 temp = 0x00;
    TR2 = 0;
    temp = (0x00 | TH2) << 8;
    return temp | TL2;
}

void Timer2_clearIntrState(){
    TF2 = 0;
    EXF2 = 0;
}