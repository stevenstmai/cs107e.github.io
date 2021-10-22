#include<stdlib.h>
#include<stdio.h>
#include<string.h>

// to make: gcc -g voidstar_ex.c -o voidstar_ex

void add_x(void *arr, int width, int len, char x) {
    // add x to each value in arr
    // assume width <= 4
    for (int i = 0; i < len; i++) {
        int num;
        memcpy(&num, (char *)arr + width * i, width);
        num += x;
        memcpy((char *)arr + width * i, &num, width);
    }
}

int main(void)
{
    char arr_char[] = {1, 50, 100, 110};
    short arr_short[] = {1, 100, 20000, 30000 };
    int arr_int[] = {1, 100, 10000, 100000, 1000000};

    int len = sizeof(arr_char) / sizeof(arr_char[0]);

    // int
    add_x(arr_int, sizeof(int), len, 5);

    for (int i = 0; i < len; i++) {
        printf("%d, ", arr_int[i]);
    }
    printf("\n");

    // char
    add_x(arr_char, sizeof(char), len, 5);

    for (int i = 0; i < len; i++) {
        printf("%d, ", arr_char[i]);
    }
    printf("\n");

    // short
    add_x(arr_short, sizeof(short), len, 5);

    for (int i = 0; i < len; i++) {
        printf("%d, ", arr_short[i]);
    }
    printf("\n");
    return 0; 
}






