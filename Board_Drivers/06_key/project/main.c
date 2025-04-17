#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_gpio.h"
int main(void)
{
    clk_enable();
    led_init();
    key_init();
    while (1)
    {
        // if (key_getvalue() == 1)
        // {
        //     led_toggle();
        // }
        if (gpio_read(GPIO1, 18) == 0)
        {
            delay_ms(10);
            if (gpio_read(GPIO1, 18) == 0)
            {
                led_toggle();
                while(gpio_read(GPIO1, 18) == 0);
            }
        }
    }
    return 1;
}