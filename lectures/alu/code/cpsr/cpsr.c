#include <stdio.h>
#include <limits.h>
#include "timer.h"

typedef unsigned (*func32_t)(unsigned, unsigned);

extern unsigned cmp32(unsigned a, unsigned b);
extern unsigned add32(unsigned a, unsigned b);
extern unsigned sub32(unsigned a, unsigned b);

extern unsigned GETCPSR(void);

#define N (1<<31)
#define Z (1<<30)
#define C (1<<29)
#define V (1<<28)

void printznc(unsigned flags)
{
    printf("z=%d,=%d,c=%d,", !!(flags&Z), !!(flags&N), !!(flags&C));
}

void printv(unsigned flags)
{
    printf("v=%d,", !!(flags&V) );
}


void print_unsigned(unsigned a, unsigned b, func32_t f, char *op)
{
    unsigned c = (*f)(a, b);
    unsigned flags = GETCPSR();
    printf("%08x%s%08x=%08x : ", a, op, b, c );
    printznc(flags);
    unsigned uge = !!(flags&C);
    printf("uge=%d\n", uge);
}

void print_signed(unsigned a, unsigned b, func32_t f, char *op)
{
    unsigned c = (*f)(a, b);
    unsigned flags = GETCPSR();
    printf("%11d%s%d=%11d : ", a, op, b, c );
    printznc(flags);
    printv(flags);
    unsigned ge = (!!(flags&N)) == (!!(flags&V));
    printf("ge=%d\n", ge);
}

void main(void)
{
  delay(1);

/*
  printf("uadd32\n");
  print_unsigned( 0x00000000, 0x00000000, &add32, "+" );
  print_unsigned( 0x00000000, 0x00000001, &add32, "+" );
  print_unsigned( 0x00000001, 0x00000000, &add32, "+" );
  print_unsigned( 0x00000001, 0x00000001, &add32, "+" );
  print_unsigned( 0x00000001, 0xFFFFFFFF, &add32, "+" );
  print_unsigned( 0xFFFFFFFF, 0x00000001, &add32, "+" );
  print_unsigned( 0xFFFFFFFF, 0xFFFFFFFF, &add32, "+" );
*/

  printf("usub32\n");
  print_unsigned( 0x00000000, 0x00000000, &sub32, "-" );
  print_unsigned( 0x00000000, 0x00000001, &sub32, "-" );
  print_unsigned( 0x00000001, 0x00000000, &sub32, "-" );
  print_unsigned( 0x00000001, 0x00000001, &sub32, "-" );
  print_unsigned( 0x00000001, 0xFFFFFFFF, &sub32, "-" );
  print_unsigned( 0xFFFFFFFF, 0x00000001, &sub32, "-" );
  print_unsigned( 0xFFFFFFFF, 0xFFFFFFFF, &add32, "-" );

/*
  printf("sub32\n");
  print_unsigned( 0x80000000,  1, &add32, "+" );
  print_unsigned( 0x80000000,  1, &sub32, "-" );
  print_unsigned( 0x7FFFFFFF,  1, &add32, "+" );
  print_unsigned( 0x7FFFFFFF,  1, &sub32, "-" );
  print_signed( 0x80000000,  1, &add32, "+" );
  print_signed( 0x80000000,  1, &sub32, "-" );
  print_signed( 0x7FFFFFFF,  1, &add32, "+" );
  print_signed( 0x7FFFFFFF,  1, &sub32, "-" );
*/
}
