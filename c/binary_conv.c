#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS     0

void
bin_recur_div (int num)
{
    if (num > 1) {
        bin_recur_div(num/2);
    }

    printf("%d", (num % 2));
}

void
bin_recur_bitwise (int num)
{
    if (num > 1) {
        bin_recur_bitwise(num >> 1);
    }

    printf("%d", (num & 1));
}

void
bin_loop (int num)
{
    int sz = sizeof(num) * 8; // Bytes to bits
    int i = 0;

    for (i = sz-1; i >= 0; i--) {
        if (num & (1 << i)) {
            printf("1");
        } else { 
            printf("0");
        }
    }
}

void
bin_loop_optimal (unsigned int num)
{
    int sz = sizeof(num) * 8; // Bytes to bits
    unsigned int i = 0;

    for (i = (1 << (sz-1)); i > 0; i /= 2) {
        if (num & i) {
            printf("1");
        } else { 
            printf("0");
        }
    }
}

int
main (void)
{
    int dec_val = 9;
    int ret_val = SUCCESS;

    printf("\nDecimal = '%d'\n", dec_val);
    bin_recur_div(dec_val);
    printf("\n");

    printf("\nDecimal = '%d'\n", dec_val-5);
    bin_recur_bitwise(dec_val-5);
    printf("\n");

    printf("\nDecimal = '%d'\n", dec_val-4);
    bin_loop(dec_val-4);
    printf("\n\n");

    printf("\nDecimal = '%d'\n", dec_val * 2);
    bin_loop_optimal(dec_val * 2);
    printf("\n\n");

    return(ret_val);
}
