#include "stm32f10x.h"
#include "Delay.h"


void delay_ms(u16 nms)
{
    while(nms--)delay_us(1000);	 	 	    
}   		    								   
void delay_us(u32 nus)
{		
    delay_10ns(nus*95);	 
}

void delay_10ns(u32 ntns) 
{         
    while(ntns--){}                  
}
