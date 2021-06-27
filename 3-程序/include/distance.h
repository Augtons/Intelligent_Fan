#ifndef _DISTANCE_H_
#define _DISTANCE_H_

#include "baseC51.h"

sbit DIS_TRIG = DIS_Trig;
sbit DIS_ECHO = DIS_Echo;

void DIS_init();

double DIS_getDistance();

#endif