#include "bsp_epittimer.h"
void epittimer_irq_handler(uint32_t gicc_iar, void *Params);
void epittimer_init(epittimer_handle *epittimer_config)
{
    epittimer_disable();
    epittimer_int_disable();
    EPIT1->CR &= ~(3U << 24);
    EPIT1->CR |= (epittimer_config->clk << 24);
    EPIT1->CR &= ~(0xFFF << 4);
    EPIT1->CR |= ((epittimer_config->psc) << 4);

    if (epittimer_config->reload_control)
    {
        EPIT1->CR |= (1 << 3);
    }
    else
    {
        EPIT1->CR &= ~(1 << 3);
    }
    EPIT1->CR |= (1 << 1);
    EPIT1->CMPR = epittimer_config->compared_value;
    EPIT1->LR = epittimer_config->reload_value;
    GIC_EnableIRQ(EPIT1_IRQn);
    sys_register_irq(EPIT1_IRQn, epittimer_irq_handler, NULL);
    epittimer_int_enable();
    // epittimer_enable();
}
void epittimer_enable()
{
    EPIT1->CR |= (1 << 0);
}
void epittimer_disable()
{
    EPIT1->CR &= ~(1 << 0);
}
void epittimer_int_enable()
{
    EPIT1->CR |= (1 << 2);
}
void epittimer_int_disable()
{
    EPIT1->CR &= ~(1 << 2);
}
void epittimer_irq_handler(uint32_t gicc_iar, void *Params)
{
    if (EPIT1->SR & (1 << 0))
    {
        epittimer_disable();
        if (gpio_read(GPIO1, 18) == 0)
        {
            led_toggle();
        }
    }
    EPIT1->SR |= 1 << 0;
}