#include <stdint.h>
#include <stdio.h>

int main(void)
{
    uint16_t x = 0xffff;
    uint32_t y = x;

    printf("%d (0x%x) -> %u (0x%x) \n", x, x, y, y);
}
