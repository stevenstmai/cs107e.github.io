#include <stdio.h>
#include <stdint.h>
#include <limits.h>

void main(void)
{
    volatile int8_t  i8  = -1;
    volatile int16_t i16 = i8;
    volatile int32_t i32 = i16;
    volatile int64_t i64 = i32;

    //printf("i16=%hd, i32=%d, i64=%lld\n", i16, i32, i64);
    //printf("i16=%hx, i32=%x, i64=%llx\n", i16, i32, i64);
}
