#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"
int main(void)
{
    clk_enable();
    gpio_init();
    while (1)
    {
        gpio_on();
        delay_ms(1000);
        gpio_off();
        delay_ms(1000);
    }
    return 1;
}