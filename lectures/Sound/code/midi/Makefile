#NAME = midi-lamb
#NAME = midi-beat
NAME = midi-song

OBJECTS =  midi.o

CFLAGS  = -I$(CS107E)/include -g -Wall -Werror -Wpointer-arith 
CFLAGS += -Og -std=c99 -ffreestanding 
CFLAGS += -mapcs-frame -fno-omit-frame-pointer -mpoke-function-name
LDFLAGS = -nostdlib -T memmap -L$(CS107E)/lib
LDLIBS = -lpi -lgcc

all : $(NAME).bin 

%.bin: %.elf
	arm-none-eabi-objcopy $< -O binary $@

%.elf: %.o $(OBJECTS)
	arm-none-eabi-gcc $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

%.o: %.s
	arm-none-eabi-as $< -o $@

%.list: %.o
	arm-none-eabi-objdump -d $< > $@

run: $(NAME).bin
	rpi-run.py -p $<

test: test.bin
	rpi-install.py -p $<

clean:
	rm -f *.o *.bin *.elf *.list *~

.PHONY: all clean install test

.PRECIOUS: %.o %.elf
