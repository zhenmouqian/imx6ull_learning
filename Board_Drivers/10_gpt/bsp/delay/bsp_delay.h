#ifndef _BSP_DELAY_H_
#define _BSP_DELAY_H_
#include "imx6ull.h"
void delay_init();
void delay_us(uint64_t us);
void delay_ms(volatile unsigned int n);


#endif // _BSP_DELAY_H_