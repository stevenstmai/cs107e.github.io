#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    int i = -10;
    for( int j = 0; j < 20; j++ )
        printf("%d\n", i++);
}
