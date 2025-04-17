#include "bsp_clk.h"
void clk_enable(void)
{
    CCM->CCGR0 = 0xFFFFFFFF;
    CCM->CCGR1 = 0xFFFFFFFF;
    CCM->CCGR2 = 0xFFFFFFFF;
    CCM->CCGR3 = 0xFFFFFFFF;
    CCM->CCGR4 = 0xFFFFFFFF;
    CCM->CCGR5 = 0xFFFFFFFF;
    CCM->CCGR6 = 0xFFFFFFFF;
}
void imx6ull_clkenable()
{
    CCM->CCSR &= (uint32_t)~(1 << 8); // 设置step_clk时钟源为osc_clk
    CCM->CCSR |= (uint32_t)1 << 2;
    CCM_ANALOG->PLL_ARM &= (uint32_t)~(0x7F);
    CCM_ANALOG->PLL_ARM |= (uint32_t)0x58;
    CCM_ANALOG->PLL_ARM |= (1 << 13);

    CCM->CACRR &= (uint32_t)~(0x7);
    CCM->CACRR |= (uint32_t)(0x1);
    CCM->CCSR &= (uint32_t)~(1 << 2);

    CCM_ANALOG->PFD_528 &= ~0x3F;
    CCM_ANALOG->PFD_528 |= 0x1B;
    CCM_ANALOG->PFD_528 &= ~(1 << 7); // 设置PFD0为352MHz

    CCM_ANALOG->PFD_528 &= ~(0x3F << 8);
    CCM_ANALOG->PFD_528 |= (0x10 << 8);
    CCM_ANALOG->PFD_528 &= ~(1 << 15); // 设置PFD1为594MHz

    CCM_ANALOG->PFD_528 &= ~(0x3F << 16);
    CCM_ANALOG->PFD_528 |= (0x18 << 16);
    CCM_ANALOG->PFD_528 &= ~(1 << 23); // 设置PFD1为594MHz

    CCM_ANALOG->PFD_528 &= ~(0x3F << 24);
    CCM_ANALOG->PFD_528 |= (0x20 << 24);
    CCM_ANALOG->PFD_528 &= ~(1 << 31); // 设置PFD1为594MHz

    CCM_ANALOG->PFD_480 &= ~0x3F;
    CCM_ANALOG->PFD_480 |= 0xC;
    CCM_ANALOG->PFD_480 &= (1 << 7);

    CCM_ANALOG->PFD_480 &= ~(0x3F << 8);
    CCM_ANALOG->PFD_480 |= (0x10 << 8);
    CCM_ANALOG->PFD_480 &= ~(1 << 15);

    CCM_ANALOG->PFD_480 &= ~(0x3F << 16);
    CCM_ANALOG->PFD_480 |= (0x11 << 16);
    CCM_ANALOG->PFD_480 &= ~(1 << 23);

    CCM_ANALOG->PFD_480 &= ~(0x3F << 24);
    CCM_ANALOG->PFD_480 |= (0x13 << 24);
    CCM_ANALOG->PFD_480 &= ~(1 << 31);

    CCM->CBCMR &= ~(0x3 << 18);
    CCM->CBCMR |= (0x1 << 18);
    CCM->CBCDR &= ~(1 << 25);
    while (CCM->CDHIPR & (1 << 5))
        ;
    // CCM->CBCDR &= ~(0x7 << 10);
    // CCM->CBCDR |= (0x2 << 10);
    // while (CCM->CDHIPR & (1 << 1))
    //     ;
    CCM->CBCDR &= ~(0x3 << 8);
    CCM->CBCDR |= (0x1 << 8);

    CCM->CSCMR1 &= ~(0x1 << 6);
    CCM->CSCMR1 &= ~(0x3F);
}