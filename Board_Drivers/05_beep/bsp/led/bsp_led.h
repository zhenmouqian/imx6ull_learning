#ifndef _BSP_LED_H_
#define _BSP_LED_H_
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
void gpio_init();
void gpio_on();
void gpio_off();
#endif // _BSP_LED_H_