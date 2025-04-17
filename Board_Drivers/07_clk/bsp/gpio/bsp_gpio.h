#ifndef _BSP_GPIO_H_
#define _BSP_GPIO_H_
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
typedef enum _gpio_direction
{
    kGPIO_DigitalInput = 0U,
    kGPIO_DigitalOnput = 1U
} gpio_pin_direction;

typedef struct _gpio_pin_config
{
    gpio_pin_direction direction;
    uint8_t outputLogic;
} gpio_pin_config;

void gpio_init(GPIO_Type *GPIO, uint8_t Pin, gpio_pin_config *config);
void gpio_write(GPIO_Type *GPIO, uint8_t Pin, uint8_t value);
uint8_t gpio_read(GPIO_Type *GPIO, uint8_t Pin);
#endif // _BSP_GPIO_H_