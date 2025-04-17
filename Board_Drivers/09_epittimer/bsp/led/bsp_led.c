#include "bsp_led.h"
#include "bsp_gpio.h"
void led_init()
{
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0);
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0x10B0);
    gpio_pin_config config = {
        .direction = kGPIO_DigitalOnput,
        .outputLogic = 1};
    gpio_init(GPIO1, 3, &config);
}
void led_on()
{
    gpio_write(GPIO1, 3, 0);
}
void led_off()
{
    gpio_write(GPIO1, 3, 1);
}
void led_toggle()
{
    if (gpio_read(GPIO1, 3) & 0x01)
    {
        GPIO1->DR &= ~(1 << 3);
    }
    else
    {
        GPIO1->DR |= (1 << 3);
    }
}