#include "uart.h"
#include "printf.h"
#include "calc.h"


static int power(int a, int b) {
    int result = 1;
    for (int i = 0; i < b; i++) {
        result *= a;
    }
    return result;
}

void main(void)
{
    const char *expr;

    uart_init();
    calc_init();

    expr = "1+1";
    printf("%s = %d\n", expr, calc_evaluate(expr));

    expr = "5-9";
    printf("%s = %d\n", expr, calc_evaluate(expr));

    expr = "7*5";
    printf("%s = %d\n", expr, calc_evaluate(expr));

    calc_add_operator('^', power);
    expr = "3^4";
    printf("%s = %d\n", expr, calc_evaluate(expr));

    printf("All done!\n");
    uart_putchar(EOT);
}

