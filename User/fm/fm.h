#ifndef _FM_H_
#define _FM_H_
#include "i2c.h"
#include "Delay.h"
#include "TEA5767.h"
#include "bsp_usart.h"

#define standby 0
#define loading 1
#define saving 2
#define searching 3

void FM_send(void);

#endif
