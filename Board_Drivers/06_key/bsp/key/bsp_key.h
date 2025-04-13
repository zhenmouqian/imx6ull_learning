#ifndef _BSP_KEY_H_
#define _BSP_KEY_H_
#include "MCIMX6Y2.h"
#include "fsl_iomuxc.h"
#include "bsp_delay.h"
void key_init();
uint8_t key_getvalue();
#endif // _BSP_KEY_H_