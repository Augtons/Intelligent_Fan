#include "lcd.h"
#include "stdio.h"

void LCD_WriteCom(u8 com)	  
{
	LCD_E = 0; 
	LCD_RS = 0;	  
	LCD_RW = 0;	   
	
	LCD_Data = com;    
	Delay1ms(1);		

	LCD_E = 1;	          
	Delay1ms(5);	 
	LCD_E = 0;
}

void LCD_WriteDat(u8 dat){
    LCD_E = 0;	
	LCD_RS = 1;	
	LCD_RW = 0;	

	LCD_Data = dat; 
	Delay1ms(1);

	LCD_E = 1;   
	Delay1ms(5);   
	LCD_E = 0;
}

void LCD_Init(){
    LCD_WriteCom(0x38);  
	LCD_WriteCom(0x0c);  
	LCD_WriteCom(0x06); 
	LCD_WriteCom(0x01);  
	LCD_WriteCom(0x80);  
}

void LCD_Clear(){
    LCD_WriteCom(0x01);
}

void LCD_Back(){
    LCD_WriteCom(0x02);
}

void LCD_SetInputMode(u8 direction, bit displayMove){
    u8 bits = 0x04;
    LCD_WriteCom(bits | direction << 1 | displayMove);
}

void LCD_DisplayEnable(u8 displayEn, u8 cursor, u8 cursorMode){
    u8 bits = 0x08;
    LCD_WriteCom(bits | displayEn << 2 | cursor << 1 | cursorMode);
}

void LCD_Move(u8 which, u8 direction, u8 step){
    u8 bits = 0x10 | which << 3 | direction << 2;
    int i;
    for(i = 0; i<step; i++){
        LCD_WriteCom(bits);
    }
}

void LCD_SetNextDataAddr(u8 addr){
    LCD_WriteCom(0x80 | addr);
}

void LCD_AddCGRAM(u8 valAddr, unsigned char *val){
    u8 i;
    valAddr <<= 3;
    for(i = 0; i<8; i++){
        LCD_WriteCom(0x40 | valAddr | i);
        LCD_WriteDat(*val++);
    }
}

void LCD_ShowString(u8 addr, unsigned char *str){
    LCD_SetNextDataAddr(addr);
    while (*str != '\0'){
        LCD_WriteDat(*str++);
    }
}

void LCD_ShowStringAtNext(unsigned char *str){
    while (*str != '\0'){
        LCD_WriteDat(*str++);
    }
}

void LCD_ShowCharAtNext(u8 val){
    LCD_WriteDat(val);
}

void LCD_ShowChar(u8 addr, u8 val){
    LCD_SetNextDataAddr(addr);
    LCD_WriteDat(val);
}

u8 LCD_GetAddrByPosition(u8 x, u8 y){
    u8 addr;
    if(x == 1){
        addr = 0x00 | y;
    }else if(x == 2){
        addr = 0x40 | y;
    }
    return addr;
}

void LCD_ShowDouble(u8 addr, double db){
    char str[8];
    sprintf(str, "%.2f", db);
    LCD_ShowString(addr, str);
}

void LCD_ShowDoubleAtNext(double db){
    char str[8];
    sprintf(str, "%.2f", db);
    LCD_ShowStringAtNext(str);
}

void LCD_ShowInt(u8 addr, int val){
    char str[8];
    sprintf(str, "%2d", val);
    LCD_ShowString(addr, str);
}

void LCD_ShowIntAtNext(int val){
    char str[8];
    sprintf(str, "%2d", val);
    LCD_ShowStringAtNext(str);
}