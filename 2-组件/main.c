#include "reg52.h"

typedef uint8 unsigned char
typedef uint16 unsigned int
sbit led = P2^0;

void delay(uint16 steps){
    while(steps--);
}

void main(){
    while(1){
        led = 1;
        delay(30000);
        led = 0;
        delay(30000);
    }
}