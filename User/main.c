
#include "stm32f10x.h"  
#include "sys.h"
#include "LCD.h"
#include "Touch.h"

int main(void)
{
	
	LCD_Init();
	LCD_Clear(RED);	
	Pen_Int_Set(ENABLE);
	Touch_Init();

	//Touch_Adjust();
	
}


