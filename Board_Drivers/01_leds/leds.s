.global _start
_start:
    //使能外设时钟
    ldr r0,=0x020c4068
    ldr r1,=0xffffffff
    str r1,[r0]

    ldr r0,=0x020c406c
    str r1,[r0]

    ldr r0,=0x020c4070
    str r1,[r0]

    ldr r0,=0x020c4074
    str r1,[r0]

    ldr r0,=0x020c4078
    str r1,[r0]

    ldr r0,=0x020c407c
    str r1,[r0]

    ldr r0,=0x020c4080
    str r1,[r0]

    //设置复用为GPIO
    ldr r0,=0x020e0068
    ldr r1,=0xfffffff5
    str r1,[r0]

    //设置电气属性
    ldr r0,=0x020e02f4
    ldr r1,=0xfffe5071
    str r1,[r0]


    //设置GPIO输出和方向
    ldr r0,=0x0209c004
    ldr r1,=0x00000008
    str r1,[r0]

    ldr r0,=0x0209c000
    ldr r1,=0x00000000
    str r1,[r0]

loop:
    b loop




