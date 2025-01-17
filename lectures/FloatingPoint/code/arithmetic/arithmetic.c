#include "printf.h"
#include "ftoa.h"

void main() {
    float a = 3.14;
    float b = 1e20;

    float c = (a + b) - b;
    float d = a + (b - b);

    char buf_c[256];
    char buf_d[256];
    ftoa(c,buf_c,5);
    ftoa(d,buf_d,5);

    printf("(3.14 + 1e20) - 1e20 = %s\n", buf_c);
    printf("3.14 + (1e20 - 1e20) = %s\n", buf_d);

}
