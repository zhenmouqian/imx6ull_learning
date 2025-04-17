#include "bsp_key.h"
#include "bsp_delay.h"
#include "bsp_gpio.h"
#include "imx6ull.h"
void key_irq_handler(uint32_t gicc_iar, void *param);
void key_init()
{
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080);
    gpio_pin_config config;
    config.direction = kGPIO_DigitalInput;
    gpio_init(GPIO1, 18, &config);

    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);
    sys_register_irq(GPIO1_Combined_16_31_IRQn, key_irq_handler, NULL);
    gpio_set_signal_int(GPIO1, 18, kGPIO_FallingEdge);
    gpio_enable_int(GPIO1, 18);
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
void key_irq_handler(uint32_t gicc_iar, void *Params)
{
    delay_ms(10);
    if (gpio_read(GPIO1, 18) == 0)
    {
        led_toggle();
    }
    gpio_clear_int(GPIO1, 18);
}
