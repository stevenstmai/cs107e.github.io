# Very simple Makefile to build program from single ASM or C file (no link)

all : button.bin c_button.bin c_button.list

CFLAGS = -g -Wall -Og -std=c99 -ffreestanding

%.bin: %.o
	arm-none-eabi-objcopy $< -O binary $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

%.o: %.s
	arm-none-eabi-as $(ASFLAGS) $< -o $@

%.list: %.o
	arm-none-eabi-objdump --no-show-raw-insn -d $< > $@

clean:
	rm -f *.o *.bin *.elf *.list *~

run: c_button.bin
	rpi-run.py $<

.PHONY: all clean run
.PRECIOUS: %.o
