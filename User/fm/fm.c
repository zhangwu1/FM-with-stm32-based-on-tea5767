#include "fm.h"


unsigned char radio_test_data[5]={0x29,0xc2,0x20,0x11,0x00};//默认频道   
uint32_t HZ_buff[100];//存储频率缓冲
uint8_t HZ_buff_current;//目前播放频率在buff中位置
TEA5767_T cerrent_FM;

void FM_Set(int HZ)
{
	int i=0;
	while(i<2)//最多搜三次
	{
		tea5767_Set(HZ, MUTE_OFF, SEARCH_ON, SEARCH_UP, FM_ADC_LEVEL);
		delay_ms(30);
		tea5767_ReadStatus(&cerrent_FM);
		if((cerrent_FM.ucReady==1)&&(abs(cerrent_FM.ulFreq-HZ)<500000))
			break;
		else{
			tea5767_Set(HZ, MUTE_OFF, SEARCH_ON, SEARCH_DOWN, FM_ADC_LEVEL);
			delay_ms(30);
		tea5767_ReadStatus(&cerrent_FM);
		if((cerrent_FM.ucReady==1)&&(abs(cerrent_FM.ulFreq-HZ)<500000))
			break;
			}
		
		i++;
	}
}

void 	FM_test(void)
{
	tea5767_Set(88100000, MUTE_OFF, SEARCH_ON, SEARCH_UP, FM_ADC_LEVEL);
	delay_ms(1000);
	tea5767_ReadStatus(&cerrent_FM);
}	

void FM_Next()
{
	printf("%d %d",HZ_buff_current,cerrent_FM.Fr_searched);
	if(cerrent_FM.Fr_searched!=0)
	{
		if(cerrent_FM.Fr_searched!=(HZ_buff_current+1)){
			HZ_buff_current++;
			FM_Set(HZ_buff[HZ_buff_current]);
			//tea5767_Set(HZ_buff[HZ_buff_current], MUTE_OFF, SEARCH_ON, SEARCH_UP, FM_ADC_LEVEL);		
			//delay_ms(100);
			tea5767_ReadStatus(&cerrent_FM);
		GUI_draw(&cerrent_FM);
		}
	}
	else{LCD_ShowString(60,40,"NOFOUND");}
}

void FM_Last()
{
	if(cerrent_FM.Fr_searched!=0)
	{
		if(HZ_buff_current>0){
			HZ_buff_current--;
			FM_Set(HZ_buff[HZ_buff_current]);
			//tea5767_Set(HZ_buff[HZ_buff_current], MUTE_OFF, SEARCH_ON, SEARCH_UP, FM_ADC_LEVEL);
			///delay_ms(100);	
			tea5767_ReadStatus(&cerrent_FM);
		GUI_draw(&cerrent_FM);			
				
		}
	}
	else{LCD_ShowString(60,40,"NOFOUND");}
}

void FM_search()
{
	unsigned long Freq = FM_FREQ_MIN;
	cerrent_FM.Fr_searched=0;//已搜到台数清零
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
				//存储
				tea5767_Set(HZ_buff[0], MUTE_OFF, SEARCH_ON, SEARCH_UP, FM_ADC_LEVEL);
				HZ_buff_current=0;
				goto OUT;
			}
			else
			{
				HZ_buff_current=0;
				tea5767_Set(101100000,MUTE_OFF,SEARCH_OFF,SEARCH_UP,FM_ADC_LEVEL);
				goto OUT;
			}
		}
		else
		{
			if(cerrent_FM.ucReady==1)
			{
				//if ((cerrent_FM.ucIFCount >= 0x31) 
		    	//&& (cerrent_FM.ucIFCount <= 0x3E) 
		    	//&& (cerrent_FM.ucAdcLevel >= 7)
				//&& (cerrent_FM.ucStereo == 1))
			//{
							tea5767_ReadStatus(&cerrent_FM);
							HZ_buff[cerrent_FM.Fr_searched]=cerrent_FM.ulFreq;
							cerrent_FM.Fr_searched=cerrent_FM.Fr_searched+1;
							LCD_ShowNum(60,130,cerrent_FM.Fr_searched,2,16);
				//}
				Freq = cerrent_FM.ulFreq + 200000;		
				tea5767_Set(Freq, MUTE_OFF, SEARCH_ON, SEARCH_UP, FM_ADC_LEVEL);
			}
			else{}
		}
	}
OUT	://跳出循环
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



