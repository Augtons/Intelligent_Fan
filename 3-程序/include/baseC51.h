#ifndef _BASEC51_H_
#define _BASEC51_H_

#include "reg52.h"
#include "intrins.h"

typedef unsigned int u16;
typedef unsigned char u8;

#define BUTTON_SETTINGS     P1^0
#define BUTTON_UP           P1^4
#define BUTTON_DOWN         P1^2

#define DIS_Trig            P2^3
#define DIS_Echo            P2^4

#define LCD_Rs              P2^7
#define LCD_Rw              P2^6
#define LCD_e               P2^5
#define LCD_Data            P0

#define TEMP_Dq             P3^5

// #define beep
#define MOTO                P2^0
#define LED                 P3^3

void delay(u16 count);
void Delay1ms(u16 time);
#endif