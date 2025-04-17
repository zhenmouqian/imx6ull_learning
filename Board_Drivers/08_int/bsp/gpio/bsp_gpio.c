#include "bsp_gpio.h"
void gpio_irq_handle(uint32_t gicc_iar, void *Params);
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
    if (config->int_enable == 1)
    {
        gpio_set_signal_int(GPIO, Pin, config->int_signal);

        if (config->gpio_irq_handler == NULL)
        {
            sys_register_irq(GPIO1_Combined_16_31_IRQn, (system_irq_handler)gpio_irq_handle, NULL);
        }
        else
        {
            sys_register_irq(GPIO1_Combined_16_31_IRQn, config->gpio_irq_handler, config->userParams);
        }
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
void gpio_enable_int(GPIO_Type *GPIO, uint8_t Pin)
{
    GPIO->IMR |= (1 << Pin);
}
void gpio_disable_int(GPIO_Type *GPIO, uint8_t Pin)
{
    GPIO->IMR &= ~(1 << Pin);
}
void gpio_clear_int(GPIO_Type *GPIO, uint8_t Pin)
{
    GPIO->ISR |= (1 << Pin);
}
void gpio_set_signal_int(GPIO_Type *GPIO, uint8_t Pin, gpio_int_signal signal)
{
    if (Pin > 15)
    {
        GPIO->ICR2 &= ~(0x3 << 2 * (Pin - 16));
        GPIO->ICR2 |= signal << 2 * (Pin - 16);
    }
    else
    {
        GPIO->ICR1 &= ~(0x3 << (2 * Pin));
        GPIO->ICR1 |= (signal << (2 * Pin));
    }
}
void gpio_irq_handle(uint32_t gicc_iar, void *Params)
{
}