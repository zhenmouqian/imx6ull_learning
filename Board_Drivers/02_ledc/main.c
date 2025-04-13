#include "main.h"
int a;
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
    MUX_GPIO1_IO03 &= ~(0xf);
    MUX_GPIO1_IO03 |= 0x5;
    PAD_GPIO1_IO03 = 0xfffe5071;
    GPIO1_IO03->GDIR |= 1 << 3;
    GPIO1_IO03->DR &= ~(1 << 3);
    // GPIO1_GDIR |= (1 << 3);
    // GPIO1_DR &= ~(1 << 3);
}
void gpio_on()
{
    GPIO1_IO03->DR &= ~(1 << 3);
    // GPIO1_DR &= ~(1 << 3);
}
void gpio_off()
{
    GPIO1_IO03->DR |= (1 << 3);
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
    // clk_enanle();
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