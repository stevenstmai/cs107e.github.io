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

    char *all[] = {a, b, c, d};
    char matrix[2][4];

    // which of these memory locations are valid to write?
    *a = 'A'; // a[0] = 'A'
    *b = 'B';
    *(char *)c = 'C'; // ?
    *d = 'D';
    all[1][1] = 'E';
    matrix[1][1] = 'F';

    printf("a = '%s' \n", a);
    printf("b = '%s' \n", b);
    printf("c = '%s' \n", c);
    printf("d = '%s' \n", d);

    printf("all[1] %p = '%s'\n", all[1], all[1]);
    printf("matrix[1] %p = '%s'\n", matrix[1], matrix[1]);

    printf("I'm %s!\n", "happy");
}

int main(void)
{
    printf("\nStarting program %s\n", __FILE__);
    strings();
    printf("\nProgram %s completed.\n\04", __FILE__);
    return 0;
}
