#include <stdio.h>

#define SUCCESS             0
//#define printf(msg, ...)    printf("\n"msg"\n", ##__VA_ARGS__)

/*
 1
 2  3
 4  5  6
 7  8  9 10
11 12 13 14 15
 */

int
main (void)
{
    int i = 0;
    int j = 0;
    int num = 0;
    int n = 5;
    int ret_val = SUCCESS;

    printf("\n\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= i; j++) {
            printf("%2d ", ++num);
        }
        printf("\n");
    }
    printf("\n\n");

    return(ret_val);
}
