#ifndef _BSP_GPIO_H_
#define _BSP_GPIO_H_
#include "imx6ull.h"
#include "bsp_int.h"
typedef enum _gpio_direction
{
    kGPIO_DigitalInput = 0U,
    kGPIO_DigitalOnput = 1U
} gpio_pin_direction;
typedef enum _gpio_int_signal
{
    kGPIO_LowLevel = 0,
    kGPIO_HighLevel = 1,
    kGPIO_RisingEdge = 2,
    kGPIO_FallingEdge = 3
} gpio_int_signal;
typedef struct _gpio_pin_config
{
    gpio_pin_direction direction;
    uint8_t outputLogic;
} gpio_pin_config;

void gpio_init(GPIO_Type *GPIO, uint8_t Pin, gpio_pin_config *config);
void gpio_write(GPIO_Type *GPIO, uint8_t Pin, uint8_t value);
uint8_t gpio_read(GPIO_Type *GPIO, uint8_t Pin);
void gpio_set_signal_int(GPIO_Type *GPIO, uint8_t Pin, gpio_int_signal signal);
void gpio_enable_int(GPIO_Type *GPIO, uint8_t Pin);
void gpio_disable_int(GPIO_Type *GPIO, uint8_t Pin);
void gpio_clear_int(GPIO_Type *GPIO, uint8_t Pin);
#endif // _BSP_GPIO_H_