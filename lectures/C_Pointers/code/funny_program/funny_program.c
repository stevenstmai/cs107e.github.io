// Self-modifying program
// Demonstrate in gdb:
// % make
// % arm-none-eabi-gdb funny_program.elf
//
// (gdb) target sim
// (gdb) load
// (gdb) b main
// (gdb) run
// (gdb) display/5i $pc
// (gdb) display/x $r1
// (gdb) si    # etc.
int main(void) 
{
    __asm__("loop:\n"
            "ldr r1, [pc, #-4]\n"
            "add r1, r1, #1\n"
            "str r1, [pc, #-12]\n"
            "mov r1, #0\n"
            "b loop"
    );
    return 0;
}
