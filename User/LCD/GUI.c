#include "GUI.h"
#include "fm.h"
extern Pen_Holder Pen_Point;//��������
extern int current_MHZ;//��ǰƵ��,��λ5�η�
extern int channel_searched;
extern int current_condition;
int TOUCH_LOC=0;//����λ��1ΪSEARCH 2ΪBEFORE 3ΪNEXT

void Judge_loc(void)
{
	if((Pen_Point.X0<50)&&(Pen_Point.Y0>50))
		TOUCH_LOC=1;
	else if((Pen_Point.X0<145)&&(Pen_Point.X0>50)&&(Pen_Point.Y0>Gus_LCM_YMAX-50))
		TOUCH_LOC=2;
	else if((Pen_Point.X0>145)&&(Pen_Point.Y0>Gus_LCM_YMAX-50))
		TOUCH_LOC=3;
}

void GUI_draw()
{
	int temp_num[2];
	temp_num[0]=current_MHZ/10;
	temp_num[1]=current_MHZ%10;
	LCD_Clear(WHITE);
	Draw_Big_Point(Pen_Point.X0,Pen_Point.Y0); //�������
	//��������
	LCD_DrawLine(0,Gus_LCM_YMAX-50,Gus_LCM_XMAX,Gus_LCM_YMAX-50);//�·�����
	//������
	LCD_DrawLine(50,Gus_LCM_YMAX,50,0);
	//�·�����
	LCD_DrawLine(50,235,Gus_LCM_XMAX,235);
	//�·�����
	LCD_DrawLine(145,Gus_LCM_YMAX-50,145,Gus_LCM_YMAX);
	//�Ϸ�����
	LCD_DrawLine(50,90,Gus_LCM_XMAX,90);
	//��������
	LCD_ShowString(20,Gus_LCM_YMAX-70,"Digital radio");
	LCD_ShowString(0,Gus_LCM_YMAX-35,"Search");
	LCD_ShowString(170,Gus_LCM_YMAX-35,"Next");
	LCD_ShowString(80,Gus_LCM_YMAX-35,"Before");
	
	LCD_ShowString(60,188,"Current Channal   ");
	LCD_ShowNum(60,210,temp_num[0],2,16);
	LCD_ShowString(80,210,".");
	LCD_ShowNum(90,210,temp_num[1],1,16);
	LCD_ShowString(100,210,"MHZ");
	
	LCD_ShowString(60,110,"Channels Searched");
	LCD_ShowNum(60,130,channel_searched,2,16);
	
	LCD_ShowString(60,20,"Current Condition");
	switch(current_condition)
	{
		case standby:
			LCD_ShowString(60,40,"Standby");
		break;
		case loading:
			LCD_ShowString(60,40,"Loading");
		break;
		case saving:
			LCD_ShowString(60,40,"Saving");
		break;
		case searching:
			LCD_ShowString(60,40,"Searching");
		break;
	}
}
