
#include "stm32f10x.h"  
#include "sys.h"
#include "bsp_usart.h"
#include "i2c.h"
#include "GUI.h"
#include "LCD.h"
#include "Touch.h"
#include "fm.h"

void NVIC_Configuration(void);//�жϳ�ʼ��
extern int TOUCH_LOC;//�����ж�
extern TEA5767_T cerrent_FM;
int main(void)
{

	NVIC_Configuration();
	USART_Config();
	I2C_Config();
	LCD_Init();	
	Pen_Int_Set(ENABLE);//ʹ�ܴ����ж�
	Touch_Init();
     //printf("xfac:%f   yfac:%f  xoff:%f  yoff:%f \n",Pen_Point.xfac,Pen_Point.yfac,Pen_Point.xoff,Pen_Point.yoff);//���ز��Բ���
	FM_dinit();//����Ĭ��Ƶ��
	
	
	while(1)
	{	
		TOUCH_LOC=0;
		Judge_loc();//�ж��Ƿ��а�ť������	
		GUI_draw(&cerrent_FM);
		Draw_Big_Point(Pen_Point.X0,Pen_Point.Y0);
		switch(TOUCH_LOC)
		{
			case SEARCH:
				FM_search();
				Pen_Point.X0=20;
				Pen_Point.Y0=50;	
			break;
		}

	}
	
}
void NVIC_Configuration(void)
{ 
  	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ��IO���ù��ܣ�ʹ���жϹ�����Ҫ������

	/* Configure one bit for preemption priority */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	   // �����ж��� Ϊ2 
	  
	/* Enable the EXTI4_IRQn Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;	// �����ж���4
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; // ����ռ�����ȼ�Ϊ2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  // ���ø����ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  // ʹ���ж���4
	NVIC_Init(&NVIC_InitStructure);							  // ��ʼ���ж���4
}

