#ifndef _BSP_LED_H_
#define _BSP_LED_H_
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
void led_init();
void led_on();
void led_off();
void led_toggle();
#endif // _BSP_LED_H_