#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"
#include "bsp_int.h"
#include "bsp_uart.h"
#include "imx6ull.h"
#include "stdio.h"
int main(void)
{
    int_init();
    imx6ull_clkenable();
    clk_enable();
    delay_init();
    led_init();
    led_toggle();
    uart_init();
    while (1)
    {
        // uart_recv_byte(&recv_ch);
        // uart_send_byte(recv_ch);
        // uart_send_bytes((uint8_t *)"hello imx6ull\r\n", sizeof("hello imx6ull\r\n"));
        printf("hello imx6ull!\r\n");
        delay_ms(1000);
        led_toggle();
    }
    return 1;
}