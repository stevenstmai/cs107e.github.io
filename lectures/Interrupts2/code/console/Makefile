NAME = console_main
BIN = $(NAME).bin

CFLAGS = -I$(CS107E)/include -g -Wall -Og -std=c99 -ffreestanding -mpoke-function-name
LDFLAGS = -nostdlib -T memmap -L$(CS107E)/lib
LDLIBS = -lpi -lgcc

all : $(NAME).bin

%.bin: %.elf
	arm-none-eabi-objcopy $< -O binary $@

%.elf: %.o
	arm-none-eabi-gcc $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

%.o: %.s
	arm-none-eabi-as $(ASFLAGS) $< -o $@

%.list: %.o
	arm-none-eabi-objdump --no-show-raw-insn -d $< > $@

run: clean $(BIN)
	rpi-run.py -p $(BIN)

interrupt: clean $(BIN)
	rpi-run.py -p $(BIN)

interrupt: CFLAGS+=-DUSE_INTERRUPTS

clean:
	rm -f *.o *.bin *.elf *.list *~

.PHONY: all clean run
.PRECIOUS: %.elf %.o

