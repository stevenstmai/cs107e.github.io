volatile static unsigned int *FSEL1 =  (unsigned int *)0x20200004;
volatile static unsigned int *FSEL2 =  (unsigned int *)0x20200008;
volatile static unsigned int *SET0  =  (unsigned int *)0x2020001c;
volatile static unsigned int *CLR0  =  (unsigned int *)0x20200028;
volatile static unsigned int *LEV0  =  (unsigned int *)0x20200034;

void main(void)
{
    *FSEL1 = 0; // config GPIO 10 as input (button)
    *FSEL2 = 1; // config GPIO 20 as output (LED)

    unsigned int bit_10 = 1 << 10;
    unsigned int bit_20 = 1 << 20;

    *SET0 = bit_20; // set GPIO 20 (LED on)

    while ((*LEV0 & bit_10) != 0) // while button not pressed
        ;

    *CLR0 = bit_20; // clear GPIO 20 (LED off)
}
