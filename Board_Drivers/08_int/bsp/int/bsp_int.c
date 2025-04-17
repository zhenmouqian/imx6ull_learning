#include "bsp_int.h"
uint32_t Nesting;
static sys_irq_table irq_table[NUMBER_OF_INT_VECTORS];
void default_irqhandler(unsigned int giccIar, void *userParam);
void int_init(void)
{
    GIC_Init();
    sys_default_irq();
    __set_VBAR((uint32_t)0x87800000);
}
void sys_default_irq()
{
    Nesting = 0;
    int i=0;
    for (i = 0; i < NUMBER_OF_INT_VECTORS; i++)
    {
        sys_register_irq(i, default_irqhandler, NULL);
    }
}
void sys_register_irq(IRQn_Type IRQn, system_irq_handler handler, void *user_param)
{
    irq_table[IRQn].handler = handler;
    irq_table[IRQn].params = user_param;
}
void SystemIrqHandler(uint32_t gicc_iar)
{
    uint32_t irqn = gicc_iar & 0x3FF;
    if (irqn > NUMBER_OF_INT_VECTORS)
    {
        return;
    }
    Nesting++;
    irq_table[irqn].handler(irqn, irq_table[irqn].params);
    Nesting--;
}
void default_irqhandler(unsigned int giccIar, void *userParam)
{
    while (1)
    {
    }
}