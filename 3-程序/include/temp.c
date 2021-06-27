#include "temp.h"

u8 TEMP_init(){
    u8 i;
    TEMP_DQ = 1;
	TEMP_DQ = 0;			 //将总线拉低480us~960us
	i = 70;	
	while(i--);//延时642us
	TEMP_DQ = 1;			//然后拉高总线，如果DS18B20做出反应会将在15us~60us后总线拉低
	i = 0;
	while(TEMP_DQ)	//等待DS18B20拉低总线
	{
		Delay1ms(1);
		i++;
		if(i>5)//等待>5MS
		{
			return 0;//初始化失败
		}
	
	}
	return 1;//初始化成功
}

void TEMP_WriteByte(u8 dat){
    u16 i, j;
	for(j=0; j<8; j++){
		TEMP_DQ = 0;	     	  //每写入一位数据之前先把总线拉低1us
		i++;
		TEMP_DQ = dat & 0x01;  //然后写入一个数据，从最低位开始
		i=6;
		while(i--); //延时68us，持续时间最少60us
		TEMP_DQ = 1;	//然后释放总线，至少1us给总线恢复时间才能接着写入第二个数值
		dat >>= 1;
	}
}

u8 TEMP_ReadByte(){
    u8 byte, bi;
	u16 i, j;	
	for(j=8; j>0; j--){
		TEMP_DQ = 0;//先将总线拉低1us
		i++;
		TEMP_DQ = 1;//然后释放总线
		i++;
		i++;//延时6us等待数据稳定
		bi = TEMP_DQ;	 //读取数据，从最低位开始读取
		/*将byte左移一位，然后与上右移7位后的bi，注意移动之后移掉那位补0。*/
		byte = (byte >> 1) | (bi << 7);						  
		i = 4;		//读取完之后等待48us再接着读取下一个数
		while(i--);
	}
	return byte;
}

void TEMP_startGetTemp(){
    TEMP_init();
	Delay1ms(1);
    TEMP_WriteByte(0xcc);//跳过ROM
    TEMP_WriteByte(0x44);//开始温度变换
}

int TEMP_getTempRaw(){
    u16 tempHighByte;
    u8 tempLowByte;
    TEMP_init();
    Delay1ms(1);
	TEMP_WriteByte(0xcc);	 //跳过ROM操作命令
	TEMP_WriteByte(0xbe);	 //发送读取温度命令
    tempLowByte = TEMP_ReadByte();
    tempHighByte = TEMP_ReadByte();
    return (tempHighByte << 8) | tempLowByte;
}

double TEMP_getTemp(){
    int tempRaw;
    double tempRaw2;
    TEMP_startGetTemp();
    Delay1ms(100);
    tempRaw = TEMP_getTempRaw();
    if(tempRaw < 0){
        tempRaw -= 1;
        tempRaw = ~tempRaw;
        tempRaw2 = 0.0625 * tempRaw;
        return (-1) * tempRaw2;
    }else{
        tempRaw2 = 0.0625 * tempRaw;
        return tempRaw2;
    }
}