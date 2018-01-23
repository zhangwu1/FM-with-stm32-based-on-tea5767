#include "fm.h"

unsigned char radio_write_data[5]={0x2e,0xdc,0x20,0x11,0x00};   

////////////////////////////////////////////////
/*搜台程序转化为命令
HZ为要搜的频率
SM为搜索模式，1搜索，0不搜
SUD，1向上搜索，0向下*/
/////////////////////////////////////////////////
void HZ_to_commend(int HZ,int SM,int SUD)
{
	int PLL=(4*(HZ-225000))/32768;
	if(SUD)
		radio_write_data[2]=radio_write_data[2]|(1<<7);//SUD位置1
	else
		radio_write_data[2]=radio_write_data[2]&(~(1<<7));//SUD位置0
	radio_write_data[1]=PLL&0xff;//11111111取出低八位
	radio_write_data[0]=PLL&0x3f00;//取出高6位
	if(SM)
		radio_write_data[0]=radio_write_data[0]|(1<<6);//SM位置1
	else
		radio_write_data[0]=radio_write_data[0]&(~(1<<6));//SM位置0
}

void FM_send(void)
{
	unsigned char i;
	//HZ_to_commend(Hz,0,0);
    I2C_StartCondition();
    I2C_SendByte(0xc0);        //TEA5767地址
	SET_SCL_LOW;
    delay_us(6);
    SET_SDA_HIGH;
    delay_us(6);
    SET_SCL_HIGH;
	while(GET_SDA_PIN);
   // {
		printf("ok");
        for(i=0;i<5;i++)
        {
            I2C_SendByte(radio_write_data[i]);
            I2C_SendAck();
        }
   // }
    I2C_StopCondition();    
}
