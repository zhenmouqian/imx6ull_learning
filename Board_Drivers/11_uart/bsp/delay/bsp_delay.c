#include "bsp_delay.h"
void delay_init()
{
    GPT1->CR = 0;
    GPT1->CR |= (1 << 15);
    while (GPT1->CR >> 15)
        ;
    GPT1->CR &= ~(0x7 << 6);
    GPT1->CR |= (0x1 << 6);
    GPT1->CR &= ~(0x1 << 9);
    GPT1->CR &= ~(0x7 << 22);

    GPT1->PR = (66 - 1);
    GPT1->OCR[0] = 0xFFFFFFFF;
    GPT1->CR |= (1 << 0);
}
void delay_us(uint64_t us)
{
    uint64_t oldCnt = GPT1->CNT;
    uint64_t newCnt = 0;
    uint64_t timepass = 0;
    while (1)
    {
        /* code */
        newCnt = GPT1->CNT;
        if (newCnt != oldCnt)
        {
            if (newCnt > oldCnt)
            {
                timepass += newCnt - oldCnt;
            }
            else
            {
                timepass += 0xFFFFFFFF - oldCnt + newCnt;
            }
            oldCnt = newCnt;
            if (timepass >= us)
            {
                break;
            }
        }
    }
}
void delay_short(volatile unsigned int n)
{
    while (n--)
    {
    }
}
void delay_ms(volatile unsigned int n)
{
    delay_us(1000 * n);
}