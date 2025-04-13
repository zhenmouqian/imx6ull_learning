#include "bsp_led.h"
void gpio_init()
{
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0);
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03,0x10B0);
    GPIO1->GDIR |= (1 << 3);
}
void gpio_on()
{
    GPIO1->DR &= ~(1 << 3);
}
void gpio_off()
{
    GPIO1->DR |= (1 << 3);
}