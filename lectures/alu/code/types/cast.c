#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <assert.h>

int main(void)
{
    for( uint8_t i = 0; i < UINT8_MAX; i++ ) {
        assert( (uint8_t) i == i );
        assert( (uint16_t)i == i );
        assert( (uint32_t)i == i );
    }
    for( uint16_t i = 0; i < UINT16_MAX; i++ ) {
        //assert( (uint8_t) i == i );
        assert( (uint16_t)i == i );
        assert( (uint32_t)i == i );
    }
    for( int8_t i = INT8_MIN; i < INT8_MAX; i++ ) {
        assert( (int8_t) i == i );
        assert( (int16_t)i == i );
        assert( (int32_t)i == i );
    }
    for( int16_t i = INT16_MIN; i < INT16_MAX; i++ ) {
        //assert( (int8_t) i == i );
        assert( (int16_t)i == i );
        assert( (int32_t)i == i );
    }
}
