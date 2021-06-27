#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "baseC51.h"

sbit key_settings = BUTTON_SETTINGS;
sbit key_up = BUTTON_UP;
sbit key_down = BUTTON_DOWN;


enum KeyValue{
    Key_Settings,
    Key_Up,
    Key_Down,

    Key_Up_Long,
    Key_Down_Long,
    Key_Settings_Long,
    
    Key_None,
};


enum KeyValue getKey();

void BTN_bindUpBtnLongClick(void (*listenerFunc)());

void BTN_bindDownBtnLongClick(void (*listenerFunc)());

void BTN_bindSettingsBtnLongClick(void (*listenerFunc)());

#endif