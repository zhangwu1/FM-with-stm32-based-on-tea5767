
#include "stm32f10x.h"  
#include "sys.h"
#include "LCD.h"
#include "Touch.h"
#include "bsp_usart.h"
#include "i2c.h"

extern Pen_Holder Pen_Point;//��������

void NVIC_Configuration(void);//�жϳ�ʼ��

int main(void)
{
	NVIC_Configuration();
	USART_Config();
	I2C_Config();
	LCD_Init();
	LCD_Clear(WHITE);	
	Pen_Int_Set(ENABLE);//ʹ�ܴ����ж�
	Touch_Init();
	//printf("xfac:%f   yfac:%f  xoff:%f  yoff:%f \n",Pen_Point.xfac,Pen_Point.yfac,Pen_Point.xoff,Pen_Point.yoff);//���ز��Բ���
	while(1)
	{
		LCD_Clear(WHITE);
	
		Draw_Big_Point(Pen_Point.X0,Pen_Point.Y0);   
	
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

