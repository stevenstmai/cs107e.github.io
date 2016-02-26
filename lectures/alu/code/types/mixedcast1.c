#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <assert.h>

int main(void)
{
    for( uint8_t i = 0; i < UINT8_MAX; i++ ) {
        int8_t j = i;
        uint8_t k = j;
        assert( i == k );
    }
    for( uint16_t i = 0; i < UINT16_MAX; i++ ) {
        int16_t j = i;
        uint16_t k = j;
        assert( i == k );
    }

    for( int8_t i = INT8_MIN; i < INT8_MAX; i++ ) {
        uint8_t j = i;
        int8_t k = j;
        assert( i == k );
    }
    for( int16_t i = INT16_MIN; i < INT16_MAX; i++ ) {
        uint16_t j = i;
        int16_t k = j;
        assert( i == k );
        //assert( i == j );
    }
    printf("sizeof(i==j)=%lx\n", sizeof(0U==0));
}
