#include <stdio.h>

#define SUCCESS     0

int
main (void)
{
    int n = 0xAA;
    int ret_val = SUCCESS;

    if ((!(n & (n >> 1))) && (!(n & (n << 1)))) {
        printf("\nYes, n '0x%x' has alternate pattern\n", n);
    }

    n = 0xCC;
    if ((!(n & (n >> 1))) && (!(n & (n << 1)))) {
        printf("\nYes, n '0x%x' has alternate pattern\n", n);
    } else {
        printf("\nNo, n '0x%x' don't have alternate pattern\n", n);
    }

    return(ret_val);
}
