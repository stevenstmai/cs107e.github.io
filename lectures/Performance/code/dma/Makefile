NAME = dma_test
OBJECTS =

CS107E = ../../../../cs107e
OPTIMIZATION = -Ofast
CFLAGS = -I$(CS107E)/include -Wall -ffreestanding -std=c99
LDFLAGS = -nostdlib -T memmap -L$(CS107E)/lib
LDLIBS = -lpiextra -lpi -lgcc

all : $(NAME).bin

%.bin: %.elf
	arm-none-eabi-objcopy $< -O binary $@

%.elf: %.o $(OBJECTS) start.o cstart.o
	arm-none-eabi-gcc $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

%.o: %.s
	arm-none-eabi-as $(ASFLAGS) $< -o $@

%.list: %.o
	arm-none-eabi-objdump  --no-show-raw-insn -d $< > $@

run: $(NAME).bin
	rpi-run.py -p $<

clean:
	rm -f *.o *.bin *.elf *.list *~

.PHONY: all clean run

.PRECIOUS: %.o %.elf

%:%.o
%:%.c
