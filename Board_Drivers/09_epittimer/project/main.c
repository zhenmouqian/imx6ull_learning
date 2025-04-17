#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"
#include "bsp_int.h"
#include "bsp_key.h"
#include "bsp_epittimer.h"
#include "imx6ull.h"
int main(void)
{
    int_init();
    imx6ull_clkenable();
    clk_enable();
    led_init();
    led_toggle();
    epittimer_handle config;
    config.clk = kEpittimer_IPG_CLK;
    config.psc = (660 - 1);
    config.reload_control = 1;
    config.reload_value = 1000;
    config.compared_value = 0;
    epittimer_init(&config);
    key_init();
    
    while (1)
    {
        delay_ms(1000);
        // led_toggle();
        // if (key_getvalue() == 1)
        // {
        //     led_toggle();
        // }
        // if (gpio_read(GPIO1, 18) == 0)
        // {
        //     delay_ms(10);
        //     if (gpio_read(GPIO1, 18) == 0)
        //     {
        //         led_toggle();
        //         while(gpio_read(GPIO1, 18) == 0);
        //     }
        // }
    }
    return 1;
}