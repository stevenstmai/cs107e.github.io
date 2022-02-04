#include "malloc.h"
#include "printf.h"
#include <stdint.h>
#include "strings.h"
#include "uart.h"

void strings(void)
{
    char a[10];
    char b[] = "dopey";
    const char *c = "happy";
    char *d = malloc(10);
    memcpy(d, "grumpy", 7);

    char *array[] = {a, b, c, d};

    // which of these memory locations are valid to write?
    *a = 'A';
    *b = 'B';
    *(char *)c = 'C'; // why typecast here?
    *d = 'D';
    array[1][1] = 'E';

    printf("a = '%s' \n", a);
    printf("b = '%s' \n", b);
    printf("c = '%s' \n", c);
    printf("d = '%s' \n", d);

    printf("array[1] %p = '%s'\n", array[1], array[1]);

    printf("I'm %s!\n", "happy");
}

int main(void)
{
    printf("\nStarting program %s\n", __FILE__);
    strings();
    printf("\nProgram %s completed.\n\04", __FILE__);
    return 0;
}
