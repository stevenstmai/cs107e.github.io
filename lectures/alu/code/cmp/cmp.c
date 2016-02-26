#include <stdint.h>
#include <stdio.h>

int main(void)
{
    uint16_t a16= 6;
    int16_t  b16 = -20;
    uint32_t a32 = 6;
    int32_t  b32 = -20;
    (b32 > a32) ? puts("-20 > 6") : puts("-20 <= 6");
    (b16 > a16) ? puts("-20 > 6") : puts("-20 <= 6");
    (b16 > a32) ? puts("-20 > 6") : puts("-20 <= 6");
    (b32 > a16) ? puts("-20 > 6") : puts("-20 <= 6");
}
