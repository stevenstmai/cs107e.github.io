#include <stdio.h>
#include "timer.h"
#include "uart.h"
#include "system.h"

void printcachesize(unsigned cache)
{
    // see Chapter B6: Caches and Write Buffers in the armv6 architecture manual
    int len = (cache & 0x3);
    int m = (cache >> 2) & 0x1;
    int assoc = (cache >> 3) & 0x7;
    int size = (cache >> 6) & 0xf;
    int p = (cache>>11) & 0x1;
    printf("len=%d, m=%d, assoc=%d, size=%d, p=%d\n",
        len, m, assoc, size, p );

    m += 2;

    // These calculations are from armv6 pB6-17
    unsigned line = (1 << (len+3));
    unsigned ways = (m << (assoc - 1));
    unsigned nsets = 1 << (size + 6 - assoc - len);
    unsigned cachesize = m << (size + 8);
    printf("size=%d bytes, line=%d bytes, nsets=%d, %d-way associative\n",
        cachesize, line, nsets, ways );
}

void printcachetype(unsigned cachetype)
{
   switch( cachetype ) {
       case 0b0000:
           printf("write-through, no lockdown\n");
           break;
       case 0b0001:
           printf("write-back, no clean, no lockdown\n");
       case 0b0010: 
       case 0b0110: 
       case 0b0111:
       case 0b1110:
       case 0b0101:
           printf("write-back, clean, lockdown\n");
           break;
       default: break;
   }
}

void printcache(void)
{
    unsigned cache = system_get_cache_type();
    printf("cache type word = %08x\n", cache );
    unsigned s = (cache & 1<<24);
    printf("%s\n", s ?
       "separate instruction and data caches" :
       "unified instruction and data cache" );
    printcachetype((cache>>25) & 0xf);
    printf("icache: ");
    printcachesize( cache      & 0xfff);
    printf("dcache: ");
    printcachesize((cache>>12) & 0xfff);

}

void main ( void )
{
    timer_init();
    uart_init();

    delay(1);

    printcache();
}
