#include "distance.h"
#include "timer.h"

static u8 timeOutted = 0;

static void timeOut(){  //8.82ms（3meter）
    timeOutted = 1;
    Timer2_enable(0);
    Timer2_clearIntrState();
}

void DIS_init(){
    Timer2_init();
    Timer2_setValue(0, 0);
    Timer2_intr_register(timeOut);
}

double DIS_getDistance() {
    u16 timeout = 100;
    timeOutted = 0;
    Timer2_setValue(0, 0);
    DIS_TRIG = 1;
    Delay1ms(12);
    DIS_TRIG = 0;
    while(!DIS_ECHO && --timeout > 0);
    if(timeout == 0){
        return -2.00;
    }
    TR2 = 1;
    while(DIS_ECHO && !timeOutted);
    TR2 = 0;
    if (!timeOutted){
        return 0.01845 * getTimer2Count();
    }else{
        return -1.00;
    }
}