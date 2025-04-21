#ifndef _BSP_UART_H_
#define _BSP_UART_H_

#include "imx6ull.h"
void uart_init();
void uart_enable();
void uart_disable();
void uart_send_byte(uint8_t ch);
void uart_send_bytes(uint8_t *bytes, uint8_t len);
void uart_recv_byte(uint8_t *byte);
void uart_setbaudrate(UART_Type *base, unsigned int baudrate, unsigned int srcclock_hz);
void putc(uint8_t c);
uint8_t getc();
#endif // _BSP_UART_H_