#ifndef _FM_H_
#define _FM_H_
#include "i2c.h"
#include "Delay.h"
#include "TEA5767.h"
#include "bsp_usart.h"
#include "GUI.h"

void 	FM_dinit(void);
void FM_search(void);
void 	FM_test(void);
void FM_Next(void);
void FM_Last(void);
void FM_Set(int HZ);
#endif
