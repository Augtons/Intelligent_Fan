#include "baseC51.h"

void delay(u16 count){
    while(count--);
}

void Delay1ms(u16 time)		//@12.000MHz
{
	unsigned char i, j;
	for(;time > 0 ; time--){
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}
}