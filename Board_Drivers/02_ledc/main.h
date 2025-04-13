#ifndef __MAIN_H_
#define __MAIN_H_
typedef unsigned int uint32_t;

typedef struct CCM
{
    volatile uint32_t CCR;
    volatile uint32_t CCDR;
    volatile uint32_t CSR;
    volatile uint32_t CCSR;
    volatile uint32_t CACRR;
    volatile uint32_t CBCDR;
    volatile uint32_t CBCMR;
    volatile uint32_t CSCMR1;
    volatile uint32_t CSCMR2;
    volatile uint32_t CSCDR1;
    volatile uint32_t CS1CDR;
    volatile uint32_t CS2CDR;
    volatile uint32_t CDCDR;
    volatile uint32_t CHSCCDR;
    volatile uint32_t CSCDR2;
    volatile uint32_t CSCDR3;
    volatile uint32_t resvered[2];
    volatile uint32_t CDHIPR;
    volatile uint32_t resvered1[2];
    volatile uint32_t CLPCR;
    volatile uint32_t CISR;
    volatile uint32_t CIMR;
    volatile uint32_t CCOSR;
    volatile uint32_t CGPR;
    volatile uint32_t CCGR0;
    volatile uint32_t CCGR1;
    volatile uint32_t CCGR2;
    volatile uint32_t CCGR3;
    volatile uint32_t CCGR4;
    volatile uint32_t CCGR5;
    volatile uint32_t CCGR6;
    volatile uint32_t resvered3[1];
    volatile uint32_t CMEOR;
} CCM_Type;

typedef struct GPIO1_IO03_Type
{
    volatile uint32_t DR;
    volatile uint32_t GDIR;
    volatile uint32_t PSR;
    volatile uint32_t ICR1;
    volatile uint32_t ICR2;
    volatile uint32_t IMR;
    volatile uint32_t ISR;
    volatile uint32_t EDGE_SEL;
} GPIO1_IO03_Type;

#define CCM_BASE (0x020C4000)
#define GPIO1_IO3_BASE (0x0209C000)
#define CCM ((CCM_Type *)CCM_BASE)
#define GPIO1_IO03 ((GPIO1_IO03_Type *)GPIO1_IO3_BASE)

#define CCM_CCGR0 *((volatile unsigned int *)0x020c4068)
#define CCM_CCGR1 *((volatile unsigned int *)0x020c406c)
#define CCM_CCGR2 *((volatile unsigned int *)0x020c4070)
#define CCM_CCGR3 *((volatile unsigned int *)0x020c4074)
#define CCM_CCGR4 *((volatile unsigned int *)0x020c4078)
#define CCM_CCGR5 *((volatile unsigned int *)0x020c407c)
#define CCM_CCGR6 *((volatile unsigned int *)0x020c4080)

#define MUX_GPIO1_IO03 *((volatile unsigned int *)0x020e0068)
#define PAD_GPIO1_IO03 *((volatile unsigned int *)0x020e02f4)

#define GPIO1_DR *((volatile unsigned int *)0x0209C000)
#define GPIO1_GDIR *((volatile unsigned int *)0x0209C004)
#define GPIO1_PSR *((volatile unsigned int *)0x0209C008)
#define GPIO1_ICR1 *((volatile unsigned int *)0x0209C00C)
#define GPIO1_ICR2 *((volatile unsigned int *)0x0209C010)
#define GPIO1_IMR *((volatile unsigned int *)0x0209C014)
#define GPIO1_ISR *((volatile unsigned int *)0x0209C018)
#define GPIO1_EDGE_SEL *((volatile unsigned int *)0x0209C01C)
#endif