
#include "stm32f10x.h"  
#include "sys.h"
#include "LCD.h"
#include "Touch.h"
#include "bsp_usart.h"
#include "i2c.h"

extern Pen_Holder Pen_Point;//触控坐标

void NVIC_Configuration(void);//中断初始化

int main(void)
{
	NVIC_Configuration();
	USART_Config();
	I2C_Config();
	LCD_Init();
	LCD_Clear(WHITE);	
	Pen_Int_Set(ENABLE);//使能触控中断
	Touch_Init();
	//printf("xfac:%f   yfac:%f  xoff:%f  yoff:%f \n",Pen_Point.xfac,Pen_Point.yfac,Pen_Point.xoff,Pen_Point.yoff);//触控测试参数
	while(1)
	{
		LCD_Clear(WHITE);
	
		Draw_Big_Point(Pen_Point.X0,Pen_Point.Y0);   
	
	}
	
}
void NVIC_Configuration(void)
{ 
  	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能IO复用功能，使用中断功能重要！！！

	/* Configure one bit for preemption priority */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	   // 设置中断组 为2 
	  
	/* Enable the EXTI4_IRQn Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;	// 配置中断线4
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; // 设置占先优先级为2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  // 设置副优先级为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  // 使能中断线4
	NVIC_Init(&NVIC_InitStructure);							  // 初始化中断线4
}

