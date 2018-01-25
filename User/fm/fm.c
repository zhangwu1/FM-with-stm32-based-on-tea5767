#include "fm.h"

unsigned char radio_write_data[5]={0x2e,0xdc,0x20,0x11,0x00};   
int current_MHZ;//单位5次方
int channel_searched;
int current_condition=standby;//0为stand by 1为正在读取数据  2为正在存数剧 3为正在搜台


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
    I2C_SendByte(0xC0);        //TEA5767地址
	while(!I2C_TestAck())
   {
		printf("ok");
        for(i=0;i<5;i++)
        {
            I2C_SendByte(radio_write_data[i]);
            I2C_SendAck();
        }
   }
    I2C_StopCondition();    
}
