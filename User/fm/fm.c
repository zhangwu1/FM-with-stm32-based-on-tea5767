#include "fm.h"

unsigned char radio_write_data[5]={0x2e,0xdc,0x20,0x11,0x00};   

////////////////////////////////////////////////
/*��̨����ת��Ϊ����
HZΪҪ�ѵ�Ƶ��
SMΪ����ģʽ��1������0����
SUD��1����������0����*/
/////////////////////////////////////////////////
void HZ_to_commend(int HZ,int SM,int SUD)
{
	int PLL=(4*(HZ-225000))/32768;
	if(SUD)
		radio_write_data[2]=radio_write_data[2]|(1<<7);//SUDλ��1
	else
		radio_write_data[2]=radio_write_data[2]&(~(1<<7));//SUDλ��0
	radio_write_data[1]=PLL&0xff;//11111111ȡ���Ͱ�λ
	radio_write_data[0]=PLL&0x3f00;//ȡ����6λ
	if(SM)
		radio_write_data[0]=radio_write_data[0]|(1<<6);//SMλ��1
	else
		radio_write_data[0]=radio_write_data[0]&(~(1<<6));//SMλ��0
}

void FM_send(void)
{
	unsigned char i;
	//HZ_to_commend(Hz,0,0);
    I2C_StartCondition();
    I2C_SendByte(0xc0);        //TEA5767��ַ
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
