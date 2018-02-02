#include "fm.h"


unsigned char radio_test_data[5]={0x29,0xc2,0x20,0x11,0x00};//Ĭ��Ƶ��   
uint32_t HZ_buff[225];//�洢Ƶ�ʻ���
TEA5767_T cerrent_FM;


void FM_search()
{
	unsigned long Freq = FM_FREQ_MIN;
	cerrent_FM.Fr_searched=0;//���ѵ�̨������
	LCD_ShowString(60,40,"Searching");
	tea5767_Set(Freq, MUTE_OFF, SEARCH_ON, SEARCH_UP, FM_ADC_LEVEL);
	while(1)
	{
		delay_ms(30);
		tea5767_ReadStatus(&cerrent_FM);
		if(cerrent_FM.ucBandLimit==1)
		{
			if(cerrent_FM.Fr_searched>0)
			{
				//�洢
				tea5767_Set(HZ_buff[0], MUTE_OFF, SEARCH_OFF, SEARCH_UP, FM_ADC_LEVEL);
				goto OUT;
			}
			else
			{
				tea5767_Set(101100000,MUTE_OFF,SEARCH_ON,SEARCH_UP,FM_ADC_LEVEL);
				goto OUT;
			}
		}
		else
		{
			if(cerrent_FM.ucReady==1)
			{
				if ((cerrent_FM.ucIFCount >= 0x31) 
		    	&& (cerrent_FM.ucIFCount <= 0x3E) 
		    	&& (cerrent_FM.ucAdcLevel >= 7)
				&& (cerrent_FM.ucStereo == 1))
				{
							HZ_buff[cerrent_FM.Fr_searched]=cerrent_FM.ulFreq;
							cerrent_FM.Fr_searched++;
							LCD_ShowNum(60,130,cerrent_FM.Fr_searched,2,16);
				}
				Freq = cerrent_FM.ulFreq + 100000;		
				tea5767_Set(Freq, MUTE_OFF, SEARCH_ON, SEARCH_UP, FM_ADC_LEVEL);
			}
			else{}
		}
	}
OUT	://����ѭ��
	tea5767_ReadStatus(&cerrent_FM);
		GUI_draw(&cerrent_FM);
}

void FM_dinit()
{
	/*unsigned char i;
    I2C_StartCondition();
    I2C_SendByte(0xc0);        //TEA5767???
    if(!I2C_TestAck())
    {
        for(i=0;i<5;i++)
        {
            I2C_SendByte(radio_test_data[i]);
            I2C_SendAck();
        }
    }
    I2C_StopCondition();   
*/
	tea5767_Set(101100000,MUTE_OFF,SEARCH_ON,SEARCH_UP,FM_ADC_LEVEL);
	tea5767_ReadStatus(&cerrent_FM);
	GUI_draw(&cerrent_FM);
}
\


