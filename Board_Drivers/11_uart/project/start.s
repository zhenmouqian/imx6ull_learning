.global _start


_start:
    ldr pc,=Reset_Handle
    ldr pc,=Undefied_Handle
    ldr pc,=Software_Handle
    ldr pc,=Prefetch_Handle
    ldr pc,=DataAbort_Handle
    ldr pc,=NotUsed_Handle
    ldr pc,=IRQ_Handle
    ldr pc,=FIQ_Handle

Reset_Handle:
    //关闭IRQ
    cpsid i

    mrc p15, 0, r0, c1, c0, 0
    bic r0, r0, #(0x1 << 0)
    bic r0, r0, #(0x1 << 1)
    bic r0, r0, #(0x1 << 2)
    bic r0, r0, #(0x1 << 11)
    bic r0, r0, #(0x1 << 12)
    mcr p15, 0, r0, c1, c0, 0

    //中断偏移
    @ ldr r0,=0x87800000
    @ dsb//数据同步
    @ isb//指令同步
    @ mcr p15, 0, r0, c12,c0, 0
    @ dsb
    @ isb

@ .global _bss_start
@ .global _bss_end
@ _bss_start:
@     .word __bss_start
@ _bss_end:
@     .word __bss_end
@     //清除BSS段
@     ldr r0,_bss_start
@     ldr r1,_bss_end
@     mov r2,#0
@ bss_loop:
@     stmia r0!,{r2}
@     cmp r0,r1
@     ble bss_loop

    //设置IRQ模式栈
    mrs r0,cpsr
    bic r0,r0,#0x1f
    orr r0,r0,#0x12
    msr cpsr,r0
    ldr sp,=0x80600000

    //设置SYS模式栈
    mrs r0,cpsr
    bic r0,r0,#0x1f
    orr r0,r0,#0x1f
    msr cpsr,r0
    ldr sp,=0x80400000

    //设置SVC模式栈
    mrs r0,cpsr
    bic r0,r0,#0x1f
    orr r0,r0,#0x13
    msr cpsr,r0
    ldr sp,=0x80200000

    //打开IRQ
    cpsie i
    b main


Undefied_Handle:
    ldr r0,=Undefied_Handle
    bx r0

Software_Handle:
    ldr r0,=Software_Handle
    bx r0

Prefetch_Handle:
    ldr r0,=Prefetch_Handle
    bx r0

DataAbort_Handle:
    ldr r0,=DataAbort_Handle
    bx r0

NotUsed_Handle:
    ldr r0,=NotUsed_Handle
    bx r0

IRQ_Handle:
    push    {lr}                         /* Save return address+4                                */
    push    {r0-r3, r12}                 /* Push caller save registers                           */

    MRS     r0, spsr                     /* Save SPRS to allow interrupt reentry                 */
    push    {r0}

    MRC     P15, 4, r1, C15, C0, 0       /* Get GIC base address                                 */
    ADD     r1, r1, #0x2000              /* r1: GICC base address                                */
    LDR     r0, [r1, #0xC]               /* r0: IAR                                              */

    push    {r0, r1}

    CPS     #0x13                        /* Change to Supervisor mode to allow interrupt reentry */

    push    {lr}                         /* Save Supervisor lr                                   */
    LDR     r2, =SystemIrqHandler
    BLX     r2                           /* Call SystemIrqHandler with param GCC                 */
    POP     {lr}

    CPS     #0x12                        /* Back to IRQ mode                                     */

    POP     {r0, r1}

    STR     r0, [r1, #0x10]              /* Now IRQ handler finished: write to EOIR              */

    POP     {r0}
    MSR     spsr_cxsf, r0

    POP     {r0-r3, r12}
    POP     {lr}
    SUBS    pc, lr, #4

FIQ_Handle:
    ldr r0,=FIQ_Handle
    bx r0


