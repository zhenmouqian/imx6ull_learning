#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "fsl_common.h"
void clk_enanle(void)
{
    CCM->CCGR0 = 0xFFFFFFFF;
    CCM->CCGR1 = 0xFFFFFFFF;
    CCM->CCGR2 = 0xFFFFFFFF;
    CCM->CCGR3 = 0xFFFFFFFF;
    CCM->CCGR4 = 0xFFFFFFFF;
    CCM->CCGR5 = 0xFFFFFFFF;
    CCM->CCGR6 = 0xFFFFFFFF;
}
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
void delay_short(volatile unsigned int n)
{
    while (n--)
    {
    }
}
void delay_ms(volatile unsigned int n)
{
    while (n--)
    {
        delay_short(0x7ff);
    }
}
int main(void)
{
    clk_enanle();
    gpio_init();
    while (1)
    {
        gpio_on();
        delay_ms(200);
        gpio_off();
        delay_ms(200);
    }
    return 1;
}