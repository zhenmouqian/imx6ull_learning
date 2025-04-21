#include "bsp_uart.h"
void uart_init()
{
    IOMUXC_SetPinMux(IOMUXC_UART1_TX_DATA_UART1_TX, 0);
    IOMUXC_SetPinMux(IOMUXC_UART1_RX_DATA_UART1_RX, 0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_TX_DATA_UART1_TX, 0x10B0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_RX_DATA_UART1_RX, 0x10B0);

    uart_disable();
    UART1->UCR2 &= ~(1 << 0);
    UART1->UCR1 &= ~(1 << 14);
    UART1->UCR2 &= ~(1 << 0);
    UART1->UCR2 |= (1 << 14) | (1 << 1) | (1 << 2) | (1 << 5); // 使能发送接受和设置8位数据
    UART1->UCR2 &= ~(1 << 6);                                  // 1位停止位
    UART1->UCR2 &= ~(1 << 8);                                  // 不使用校验
    UART1->UCR3 |= (1 << 2);

    // UART1->UFCR &= ~(0x7 << 7);
    // UART1->UFCR |= (0x5 << 7);
    // UART1->UBIR = 71;
    // UART1->UBMR = 3124;
    uart_setbaudrate(UART1, 115200, 80000000);
    uart_enable();
}
void uart_disable()
{
    UART1->UCR1 &= ~(1 << 0);
}
void uart_enable()
{
    UART1->UCR1 |= (1 << 0);
}
void uart_send_byte(uint8_t ch)
{
    UART1->UTXD = (ch) & 0xFF;
    while (((UART1->USR2 >> 3) & 0x1) == 0)
        ;
}
void uart_send_bytes(uint8_t *bytes, uint8_t len)
{
    int i = 0;
    for (i = 0; i < len; i++)
    {
        uart_send_byte(*(bytes + i));
    }
}
void putc(uint8_t c)
{
    UART1->UTXD = (c) & 0xFF;
    while (((UART1->USR2 >> 3) & 0x1) == 0)
    {
    };
}
uint8_t getc()
{
    uint8_t res;
    while ((UART1->USR2 & 0x1) == 0)
    {
    };
    res = UART1->URXD & 0xFF;
    return res;
}
void uart_recv_byte(uint8_t *byte)
{
    while ((UART1->USR2 & 0x1) == 0)
    {
    };
    *byte = UART1->URXD & 0xFF;
}
void uart_setbaudrate(UART_Type *base, unsigned int baudrate, unsigned int srcclock_hz)
{
    uint32_t numerator = 0u;   // 分子
    uint32_t denominator = 0U; // 分母
    uint32_t divisor = 0U;
    uint32_t refFreqDiv = 0U;
    uint32_t divider = 1U;
    uint64_t baudDiff = 0U;
    uint64_t tempNumerator = 0U;
    uint32_t tempDenominator = 0u;

    /* get the approximately maximum divisor */
    numerator = srcclock_hz;
    denominator = baudrate << 4;
    divisor = 1;

    while (denominator != 0)
    {
        divisor = denominator;
        denominator = numerator % denominator;
        numerator = divisor;
    }

    numerator = srcclock_hz / divisor;
    denominator = (baudrate << 4) / divisor;

    /* numerator ranges from 1 ~ 7 * 64k */
    /* denominator ranges from 1 ~ 64k */
    if ((numerator > (UART_UBIR_INC_MASK * 7)) || (denominator > UART_UBIR_INC_MASK))
    {
        uint32_t m = (numerator - 1) / (UART_UBIR_INC_MASK * 7) + 1;
        uint32_t n = (denominator - 1) / UART_UBIR_INC_MASK + 1;
        uint32_t max = m > n ? m : n;
        numerator /= max;
        denominator /= max;
        if (0 == numerator)
        {
            numerator = 1;
        }
        if (0 == denominator)
        {
            denominator = 1;
        }
    }
    divider = (numerator - 1) / UART_UBIR_INC_MASK + 1;

    switch (divider)
    {
    case 1:
        refFreqDiv = 0x05;
        break;
    case 2:
        refFreqDiv = 0x04;
        break;
    case 3:
        refFreqDiv = 0x03;
        break;
    case 4:
        refFreqDiv = 0x02;
        break;
    case 5:
        refFreqDiv = 0x01;
        break;
    case 6:
        refFreqDiv = 0x00;
        break;
    case 7:
        refFreqDiv = 0x06;
        break;
    default:
        refFreqDiv = 0x05;
        break;
    }
    /* Compare the difference between baudRate_Bps and calculated baud rate.
     * Baud Rate = Ref Freq / (16 * (UBMR + 1)/(UBIR+1)).
     * baudDiff = (srcClock_Hz/divider)/( 16 * ((numerator / divider)/ denominator).
     */
    tempNumerator = srcclock_hz;
    tempDenominator = (numerator << 4);
    divisor = 1;
    /* get the approximately maximum divisor */
    while (tempDenominator != 0)
    {
        divisor = tempDenominator;
        tempDenominator = tempNumerator % tempDenominator;
        tempNumerator = divisor;
    }
    tempNumerator = srcclock_hz / divisor;
    tempDenominator = (numerator << 4) / divisor;
    baudDiff = (tempNumerator * denominator) / tempDenominator;
    baudDiff = (baudDiff >= baudrate) ? (baudDiff - baudrate) : (baudrate - baudDiff);

    if (baudDiff < (baudrate / 100) * 3)
    {
        base->UFCR &= ~UART_UFCR_RFDIV_MASK;
        base->UFCR |= UART_UFCR_RFDIV(refFreqDiv);
        base->UBIR = UART_UBIR_INC(denominator - 1); // 要先写UBIR寄存器，然后在写UBMR寄存器，3592页
        base->UBMR = UART_UBMR_MOD(numerator / divider - 1);
    }
}
int raise(int signum)
{
    return 0;
}