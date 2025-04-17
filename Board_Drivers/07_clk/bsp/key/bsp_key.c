#include "bsp_key.h"
#include "bsp_delay.h"
#include "bsp_gpio.h"
void key_init()
{
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF000);
    gpio_pin_config config = {
        .direction = kGPIO_DigitalInput};
    gpio_init(GPIO1, 18, &config);
}
uint8_t key_getvalue()
{
    uint8_t ret = 0;
    static uint8_t release = 1;
    if (release == 1 && gpio_read(GPIO1, 18) == 0)
    {
        delay_ms(10);
        release = 0;
        if (gpio_read(GPIO1, 18) == 0)
        {
            ret = 1;
        }
    }
    else if (gpio_read(GPIO1, 18) == 1)
    {
        release = 1;
        ret = 0;
    }
    return ret;
}