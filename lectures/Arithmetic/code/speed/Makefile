CFLAGS = -I$(CS107E)/include -g -Wall -Og -std=c99 -ffreestanding -mapcs-frame -fno-omit-frame-pointer
LDFLAGS = -nostdlib -T memmap -L$(CS107E)/lib
LDLIBS = -lpi -lpiextra

# Setting DEFAULT sets the default program that make
# will build. You can also build specific
# ones to build (e.g. 'make lines-2d.bin').
DEFAULT = timing.bin

HELP_OBJS = helpers.o

# -march=armv6 -O10

# -O3
#  -falign-labels  -falign-jumps

.PRECIOUS: %.o %.elf

all: $(DEFAULT)

run: all
	rpi-run.py -p $(DEFAULT)

%.bin: %.elf
	arm-none-eabi-objcopy $< -O binary $@

%.o: %.s
	arm-none-eabi-as $(ASFLAGS) $< -o $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $<

%.elf: %.o  $(HELP_OBJS)
	arm-none-eabi-gcc $(LDFLAGS) $^ $(LDLIBS) -o $@ 

# /opt/gnuarm/lib/gcc/arm-none-eabi/4.8.3/libgcc.a

clean:
	rm -f *.bin *.elf *.list *~ *.o \#* *.bak

