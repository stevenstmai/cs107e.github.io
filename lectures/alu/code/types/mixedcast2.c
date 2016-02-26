#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <assert.h>

int main(void)
{
    assert( (uint8_t )-1 == UINT8_MAX );
    assert( (uint16_t)-1 == UINT16_MAX );
    assert( (uint32_t)-1 == UINT32_MAX );

    /*
    **    Technically: u = i + UINT_MAX + 1
    */

    for( uint8_t i = 0; i < UINT8_MAX; i++ ) {
        int32_t j = i;
        uint32_t k = i;
        assert( i == j );
        assert( j == k );
    }

    for( int8_t i = INT8_MIN; i < INT8_MAX; i++ ) {
        uint32_t j = i;
        int32_t k = i;
        assert( i == j );
        assert( j == k );
    }
}
