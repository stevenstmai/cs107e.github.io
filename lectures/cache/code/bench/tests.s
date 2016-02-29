.globl ARMTEST0
ARMTEST0:
    subs r0,r0,#1
    bne ARMTEST0
    bx lr

    nop

.globl ARMTEST1
ARMTEST1:
    subs r0,r0,#1
    subs r0,r0,#1
    subs r0,r0,#1
    subs r0,r0,#1
    subs r0,r0,#1
    subs r0,r0,#1
    subs r0,r0,#1
    subs r0,r0,#1
    bne ARMTEST1
    bx lr

.globl ARMTEST2
ARMTEST2:
    subs r0,r0,#1
    subs r0,r0,#1
    subs r0,r0,#1
    subs r0,r0,#1
    subs r0,r0,#1
    subs r0,r0,#1
    subs r0,r0,#1
    subs r0,r0,#1
    subs r0,r0,#1
    subs r0,r0,#1
    subs r0,r0,#1
    subs r0,r0,#1
    subs r0,r0,#1
    subs r0,r0,#1
    subs r0,r0,#1
    subs r0,r0,#1
    bne ARMTEST2
    bx lr

.globl ARMTEST3
ARMTEST3:
    subs r0,r0,#1
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    subs r0,r0,#1
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    subs r0,r0,#1
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    subs r0,r0,#1
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    subs r0,r0,#1
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    subs r0,r0,#1
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    subs r0,r0,#1
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    subs r0,r0,#1
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    bne ARMTEST3
    bx lr

.globl ARMTEST4
ARMTEST4:
    mov r1, #1
    push {r1}
loop:
    ldr r1, [sp]
    subs r0,r0,#1
    bne loop
    pop {r1}
    bx lr

.global ARMTEST5
ARMTEST5:
    ldr r1, [r0]
    subs r0, r0, #1
    bne ARMTEST5
    bx lr
