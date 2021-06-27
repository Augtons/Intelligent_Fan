#include "lcd.h"
#include "button.h"
#include "temp.h"
#include "timer.h"
#include "distance.h"

#define reverse(x) (x == 0 ? 1 : 0)
#define clearSpeedView LCD_ShowChar(0x48, ' ');\
        LCD_ShowChar(0x4a, ' ');\
        LCD_ShowChar(0x4c, ' ');\
        LCD_ShowChar(0x4e, ' ')
sbit moto = P2^0;
// sbit beep = P2^2;
sbit led = LED;

char code sheshidu[8] = {0x10, 0x06, 0x09, 0x08, 0x08, 0x09, 0x06, 0x00};
u8 mode = 0;     //����ģʽ���Զ�
u8 nowToSet = 0; //������������
u8 nowSpeed = 0; //��ǰ��λ�������ֶ������Զ���
int up = 30;    //�¶�����
int down = 20;  //�¶�����

double temp;
double distance;

int nowLed_T = 1000;
u8 ledMode = 0;


u16 count0 = 0;  //Timer0��ʱ�жϼ���
u16 motoSpeedCtrlCount = 0;


void setWorkingMode(u8 theMode);
void changeSettingView();
void changeUPView();
void changeDownView();
void changeNowSpeedView();

void motoSpeedCtrl();

void keyDownClick();
void keyUpClick();

void empty(){           //�պ�������ֹ��ָ������µ�Ƭ������

}

void settingBTNLongClick(){     //�������ü����л�����ģʽ���Զ����ֶ���
    setWorkingMode(reverse(mode));
}

void autoLCDView(){     //��ʼ���Զ�������
    LCD_Clear();
    LCD_ShowString(0x00, "Auto");
    LCD_ShowString(0x09, "H:");
    LCD_ShowString(0x49, "L:");
    LCD_ShowChar(0x0D, 0);
    LCD_ShowChar(0x4D, 0);
    changeSettingView();
    changeUPView();
    changeDownView();
}

void manualLCDView(){       //��ʼ���ֶ�������
    LCD_Clear();
    LCD_ShowString(0x00, "Manual");
    LCD_ShowString(0x08, "0 1 2 3");
    changeNowSpeedView();
}

void changeUPView(){        //���������¶���ʾ
    LCD_ShowInt(0x0B, up);
}

void changeDownView(){
    LCD_ShowInt(0x4B, down);
}

void changeSettingView(){
    if(nowToSet == 1){  //������������
        LCD_ShowChar(0x08, '>');
        LCD_ShowChar(0x48, ' ');
    }else{
        LCD_ShowChar(0x08, ' ');
        LCD_ShowChar(0x48, '>');
    }
}

void changeNowSpeedView(){      //�ֶ�����
    clearSpeedView;
    if(nowSpeed == 0){
        LCD_ShowChar(0x48, '^');
    }else if(nowSpeed == 1){
        LCD_ShowChar(0x4a, '^');
    }else if(nowSpeed == 2){
        LCD_ShowChar(0x4c, '^');
    }else if(nowSpeed == 3){
        LCD_ShowChar(0x4e, '^');
    }
}

void ledCtrl(){     //��ʱ��1LED����
    Timer1_setValue(0xfc, 0x66);
    if(motoSpeedCtrlCount >= nowLed_T){
        led = ~led;
        motoSpeedCtrlCount = 0;
    }else{
        motoSpeedCtrlCount ++;
    }
}

void distanceAndTemp(){     //�Զ�ģʽ�µĶ�ʱ��0�жϺ���
    Timer0_setValue(0xfc, 0x66);
    if(count0 <= 500){
        count0 ++;
    }else{
        temp = TEMP_getTemp();
        distance = DIS_getDistance();
        TR2 = 0;

        if(temp >= up){ //�л���ʱ��1������ʽ������LED�ƻ���PWM��
            if(ledMode == 0){
                Timer1_enable(0);
                Timer1_setValue(0xfc, 0x66);
                Timer1_intr_register(ledCtrl);
                Timer1_enable(1);
                ledMode = 1;
            }
        }else{
            if(ledMode == 1){
                Timer1_enable(0);
                Timer1_setValue(0xfc, 0x66);
                Timer1_intr_register(motoSpeedCtrl);
                Timer1_enable(1);
                led = 1;
                ledMode = 0;
            }
        }
        if(temp >= up){
            nowLed_T = 1000 / (((temp - up)/10 + 1)*((temp - up)/10 + 1));
        }
        if (distance <= 10 && distance > 0 || distance == -1.0){
            nowSpeed = 0;
            moto = 0;
        }else{
            if (temp >= up){
                moto = 1;
                nowSpeed = 3;
            }else if(temp >= down){
                nowSpeed = 2;
                led = 1;
            }else{
                nowSpeed = 0;
                led = 1;
            }
        }
        LCD_ShowDouble(0x40, temp);
        LCD_ShowCharAtNext(0);
        count0 = 0;
    }
    
}

void setWorkingMode(u8 theMode){
    if(theMode == 1){   //�ֶ�
        Timer0_enable(0);
        mode = 1;
        manualLCDView();
        BTN_bindUpBtnLongClick(empty);
        BTN_bindDownBtnLongClick(empty);
        
    }else{
        mode = 0;
        autoLCDView();
        BTN_bindUpBtnLongClick(keyUpClick);
        BTN_bindDownBtnLongClick(keyDownClick);
        Timer0_enable(1);
    }
}

void keyUpClick(){
    if(mode == 0){              //�Զ�ģʽ
        if(nowToSet == 1){      //������������
            if(up < 80){
                up++;
                changeUPView();
            }
        }else{
            if(down < up){
                down++;
                changeDownView();
            }
        }
    }else{                      //�ֶ�ģʽ
        if(nowSpeed < 3){
            nowSpeed ++;
            changeNowSpeedView();
        }
    }
    
}

void keyDownClick(){
    if(mode == 0){              //�Զ�ģʽ
        if(nowToSet == 1){      //������������
            if(up > down){
                up--;
                changeUPView();
            }
        }else{
            if(down > 1){
                down--;
                changeDownView();
            }
        }
    }else{                      //�ֶ�ģʽ
        if(nowSpeed > 0){
            nowSpeed --;
            changeNowSpeedView();
        }
    }
}

void motoSpeedCtrl(){       //Timer1�ж�
    Timer1_setValue(0xfc, 0x66);
    if(motoSpeedCtrlCount <= 10){
        if(nowSpeed == 3){
            moto = 1;
        }else if(nowSpeed == 2){
            if(motoSpeedCtrlCount <= 6){
                moto = 1;
            }else{
                moto = 0;
            }
        }else if(nowSpeed == 1){
            if(motoSpeedCtrlCount <= 3){
                moto = 1;
            }else{
                moto = 0;
            }
        }else if(nowSpeed == 0){
            moto = 0;
        }
        motoSpeedCtrlCount ++;
    }else{
        motoSpeedCtrlCount = 0;
    }
}

void main() {
    u8 count = 0;
    moto = 0;

    LCD_Init();
    Timer1_init();
    Timer0_init();
    DIS_init();
    LCD_AddCGRAM(0, sheshidu);

    //��������
    LCD_ShowString(0x00, "Auto");
    LCD_ShowString(0x40, "Loading");
    for(count = 0; count < 6; count++){
        //beep = ~beep;
        led = ~led;
        Delay1ms(500);
        LCD_ShowCharAtNext('.');
    }
    //����Ϊ��������

    setWorkingMode(mode);
    BTN_bindSettingsBtnLongClick(settingBTNLongClick);
    
    /*��ʱ��1����PWM���Ƶ���ٶ� */
    Timer1_setValue(0xfc, 0x66);
    Timer1_intr_register(motoSpeedCtrl);
    Timer1_enable(1);

    /*��ʱ��0���ڶ�ʱ����¶Ⱥ;��� */
    Timer0_setValue(0xfc, 0x66);
    Timer0_intr_register(distanceAndTemp);
    while(1){
        if(mode == 0){  //�Զ�ģʽ
            switch(getKey()){
                case Key_Settings:
                    nowToSet = reverse(nowToSet);
                    changeSettingView();
                    TR0 = 1;
                    break;
                case Key_Up:
                    keyUpClick();
                    TR0 = 1;
                    break;
                case Key_Down:
                    keyDownClick();
                    TR0 = 1;
                    break;
                case Key_Up_Long:
                    TR0 = 1;
                    break;
                case Key_Down_Long:
                    TR0 = 1;
                    break;
            }
        }else{         //�ֶ�ģʽ
            switch(getKey()){
                case Key_Up:
                    keyUpClick();  
                    break;
                case Key_Down:
                    keyDownClick();
                    break;

            }
        }
    }
}