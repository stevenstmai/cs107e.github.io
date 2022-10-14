 unsigned int *FSEL1 =  (unsigned int *)0x20200004;
 unsigned int *FSEL2 =  (unsigned int *)0x20200008;
 unsigned int *SET0  =  (unsigned int *)0x2020001c;
 unsigned int *CLR0  =  (unsigned int *)0x20200028;
 unsigned int *LEV0  =  (unsigned int *)0x20200034;

void main(void)
{
    *FSEL1 = 0; // configure GPIO 10 as input
    *FSEL2 = 1; // configure GPIO 20 as output

    while (1) {

        // wait until GPIO 10 is low (button press)
        while ((*LEV0 & (1 << 10)) != 0) ;

        // set GPIO 20 high
        *SET0 = 1 << 20;

        // wait until GPIO 10 is high (button release)
        while ((*LEV0 & (1 << 10)) == 0) ;

        // clear GPIO 20
        *CLR0 = 1 << 20;
    }
}
