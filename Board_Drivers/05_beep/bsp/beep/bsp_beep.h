#ifndef _BSP_BEEP_H_
#define _BSP_BEEP_H_

#include "MCIMX6Y2.h"
#include "fsl_iomuxc.h"
void beep_init();
void beep_off();
void beep_on();
#endif // _BSP_BEEP_H_