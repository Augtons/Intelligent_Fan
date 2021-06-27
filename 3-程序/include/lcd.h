#ifndef _LCD_H_
#define _LCD_H_
#include "baseC51.h"

sbit LCD_RS = LCD_Rs;
sbit LCD_RW = LCD_Rw;
sbit LCD_E = LCD_e;

void LCD_WriteCom(u8 com);

void LCD_WriteDat(u8 dat);

void LCD_Init();

void LCD_Clear();

void LCD_Back();

void LCD_SetInputMode(u8 direction, bit displayMove);

//displayEn 1使能显示
//cursor 1:显示光标
//cursorMode 1:光标不闪烁
void LCD_DisplayEnable(u8 displayEn, u8 cursor, u8 cursorMode);

//which 0:光标 1:内容
//direction 0:左    1:右
void LCD_Move(u8 which, u8 direction, u8 step);

void LCD_SetNextDataAddr(u8 addr);

void LCD_AddCGRAM(u8 addr, unsigned char *val);

void LCD_ShowString(u8 addr, unsigned char *str);

void LCD_ShowStringAtNext(unsigned char *str);

void LCD_ShowCharAtNext(u8 valAdd);

void LCD_ShowChar(u8 addr, u8 val);

u8 LCD_GetAddrByPosition(u8 x, u8 y);

void LCD_ShowDouble(u8 addr, double db);

void LCD_ShowDoubleAtNext(double db);

void LCD_ShowInt(u8 addr, int val);

void LCD_ShowIntAtNext(int val);

#endif

