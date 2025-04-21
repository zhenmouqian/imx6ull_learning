#ifndef _BSP_INT_H_
#define _BSP_INT_H_
#include "imx6ull.h"
typedef void (*system_irq_handler)(uint32_t gicc_iar, void *Params);
void int_init(void);
void SystemIrqHandler(uint32_t gicc_iar);
void sys_register_irq(IRQn_Type IRQn, system_irq_handler handler, void *user_param);
void sys_default_irq();
typedef struct _sys_irq_table
{
    system_irq_handler handler;
    void *params;
} sys_irq_table;

#endif // _BSP_INT_H_