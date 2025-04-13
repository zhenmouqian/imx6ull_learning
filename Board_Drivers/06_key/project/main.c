#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"
#include "bsp_key.h"
int main(void)
{
    clk_enable();
    led_init();
    key_init();
    while (1)
    {
        if (key_getvalue() == 1)
        {
            led_toggle();
        }
        // if (key_read() == 0)
        // {
        //     delay_ms(10);
        //     if (key_read() == 0)
        //     {
        //         gpio_toggle();
        //         while(key_read() == 0);
        //     }
        // }
    }
    return 1;
}