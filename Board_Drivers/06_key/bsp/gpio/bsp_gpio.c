#include "bsp_gpio.h"
void gpio_init(GPIO_Type *GPIO, uint8_t Pin, gpio_pin_config *config)
{
    if (config->direction == kGPIO_DigitalInput)
    {
        GPIO->GDIR &= ~(1 << Pin);
    }
    else
    {
        GPIO->GDIR |= (1 << Pin);
        gpio_write(GPIO, Pin, config->outputLogic);
    }
}
void gpio_write(GPIO_Type *GPIO, uint8_t Pin, uint8_t value)
{
    if (value)
    {
        GPIO->DR |= (1 << Pin);
    }
    else
    {
        GPIO->DR &= ~(1 << Pin);
    }
}
uint8_t gpio_read(GPIO_Type *GPIO, uint8_t Pin)
{
    uint8_t ret = 0;
    ret = (GPIO->DR >> Pin) & 0x01;
    return ret;
}