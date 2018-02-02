
#include "stm32f10x.h"  
#include "sys.h"
#include "bsp_usart.h"
#include "i2c.h"
#include "GUI.h"
#include "LCD.h"
#include "Touch.h"
#include "fm.h"

void NVIC_Configuration(void);//中断初始化
extern int TOUCH_LOC;//按键判断
extern TEA5767_T cerrent_FM;
int main(void)
{

	NVIC_Configuration();
	USART_Config();
	I2C_Config();
	LCD_Init();	
	Pen_Int_Set(ENABLE);//使能触控中断
	Touch_Init();
     //printf("xfac:%f   yfac:%f  xoff:%f  yoff:%f \n",Pen_Point.xfac,Pen_Point.yfac,Pen_Point.xoff,Pen_Point.yoff);//触控测试参数
	FM_dinit();//播放默认频道
	
	
	while(1)
	{	
		TOUCH_LOC=0;
		Judge_loc();//判断是否有按钮被按下	
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

