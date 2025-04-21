#ifndef _BSP_EPITTIMER_H_
#define _BSP_EPITTIMER_H_
#include "imx6ull.h"
#include "bsp_int.h"
#include "bsp_led.h"
#include "bsp_gpio.h"
typedef enum _epittimer_clk
{
    kEpittimer_Off = 0,
    kEpittimer_IPG_CLK = 1,
    kEpittimer_IPG_CLK_32K = 2,
    kEpittimer_IPG_CLK_HIGH = 3,
} epittimer_clk;
typedef struct _epittimer_handle
{
    epittimer_clk clk;
    uint8_t reload_control;
    uint32_t reload_value;
    uint32_t psc;
    uint32_t compared_value;
} epittimer_handle;

void epittimer_init(epittimer_handle *epittimer_config);
void epittimer_enable(void);
void epittimer_disable(void);
void epittimer_int_enable(void);
void epittimer_int_disable(void);
#endif // _BSP_EPITTIMER_H_