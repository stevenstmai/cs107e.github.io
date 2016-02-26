.globl _start
_start:
    mov sp,#0x8000
    bl _cstart
hang: b hang

.global add32
add32:
    adds r0, r0, r1
    bx lr

.global sub32
sub32:
    subs r0, r0, r1
    bx lr

.global cmp32
cmp32:
    cmp r0, r1
    bx lr

.global GETCPSR
GETCPSR:
    mrs r0, cpsr
    bx lr
