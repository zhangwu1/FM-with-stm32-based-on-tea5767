#include "GUI.h"
extern Pen_Holder Pen_Point;//��������

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
	LCD_Clear(WHITE);
	Draw_Big_Point(Pen_Point.X0,Pen_Point.Y0); //�������
	//��������
	LCD_DrawLine(0,Gus_LCM_YMAX-50,Gus_LCM_XMAX,Gus_LCM_YMAX-50);//�·�����
	//������
	LCD_DrawLine(50,Gus_LCM_YMAX,50,0);
	//�Ϸ�����
	LCD_DrawLine(50,50,Gus_LCM_XMAX,50);
	//�·�����
	LCD_DrawLine(145,Gus_LCM_YMAX-50,145,Gus_LCM_YMAX);
	//��������
	LCD_ShowString(20,Gus_LCM_YMAX-70,"Digital radio");
	LCD_ShowString(0,Gus_LCM_YMAX-35,"Search");
	LCD_ShowString(170,Gus_LCM_YMAX-35,"Next");
	LCD_ShowString(80,Gus_LCM_YMAX-35,"Before");
}
