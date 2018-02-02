#ifndef _GUI_H_
#define _GUI_H_
#include "stm32f10x.h"
#include "LCD.h"
#include "Touch.h"
#include "fm.h"
#include "TEA5767.h"

enum
{
	SEARCH =1,
	LAST =2,
	NEXT =3
};

void GUI_draw(TEA5767_T *_tStatus);
void Judge_loc(void);

#endif
