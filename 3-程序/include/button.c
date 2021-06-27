#include "button.h"
#include "timer.h"
#include "lcd.h"

static void (*Btn_up_Long_Click_Function)();
static void (*Btn_down_Long_Click_Function)();
static void (*Btn_settings_Long_Click_Function)();

static u16 timeout0 = 0x9C40;
#define BTN_TIME_OUT (timeout0 == 0)


static void BTN_UP_Longclick(){
    while(key_up == 0){
        Btn_up_Long_Click_Function();
        Delay1ms(150);
    }
}

static void BTN_DOWN_Longclick(){
    while(key_down == 0){
        Btn_down_Long_Click_Function();
        Delay1ms(150);
    }
}

static void BTN_SETTINGS_Longclick(){
    Btn_settings_Long_Click_Function();
    while(!key_settings);
}

enum KeyValue getKey(){
    //******//
    // u8 flag = 0;

    key_down = 1;
    key_up = 1;
    key_settings = 1;
    timeout0 = 0xA120;

    if(key_settings == 0){
        delay(1000);
        if(key_settings == 0){
            //******//
            TR0 = 0;
            while(!key_settings && !(BTN_TIME_OUT)){
                timeout0 --;
            }
            if(BTN_TIME_OUT){
                BTN_SETTINGS_Longclick();
                return Key_Settings_Long;
            }else{
                return Key_Settings;
            }
        }
    }else if(key_up == 0){
        delay(1000);
        if(key_up == 0){
            //******//
            TR0 = 0;
            while(!key_up && !(BTN_TIME_OUT)){
                timeout0 --;
            }
            if(BTN_TIME_OUT){
                BTN_UP_Longclick();
                return Key_Up_Long;
            }else{
                
                return Key_Up;
            }
            
        }
    }else if(key_down == 0){
        delay(1000);
        if(key_down == 0){
            //******//
            TR0 = 0;
            while(!key_down && !(BTN_TIME_OUT)){
                timeout0 --;
            }
            if(BTN_TIME_OUT){
                BTN_DOWN_Longclick();
                
                return Key_Down_Long;
            }else{
                
                return Key_Down;
                
            }
        }
    }
    return Key_None;
}

void BTN_bindUpBtnLongClick(void (*listenerFunc)()){
    Btn_up_Long_Click_Function = listenerFunc;
}

void BTN_bindDownBtnLongClick(void (*listenerFunc)()){
    Btn_down_Long_Click_Function = listenerFunc;
}

void BTN_bindSettingsBtnLongClick(void (*listenerFunc)()){
    Btn_settings_Long_Click_Function = listenerFunc;
}