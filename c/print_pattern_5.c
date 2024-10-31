#include <stdio.h>

#define SUCCESS             0
//#define printf(msg, ...)    printf("\n"msg"\n", ##__VA_ARGS__)

/*
    Print pattern using not more than two loops
                *
               ***
              *****
             *******
            *********
    
    Observation:
     . Rows     = 5 --> n       ==> Outer loop
     . Columns  = 9 --> 2n - 1  ==> Inner loop

     URL: https://www.youtube.com/watch?v=KdM6OrvcjPI
 */
int
main (void)
{
    int i = 0;
    int j = 0;
    int n = 5;
    int ret_val = SUCCESS;

    printf("\n\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= ((2*n)-1); j++) {
            if ((j >= (n - (i - 1))) && (j <= (n + (i -1)))) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\n\n");

    return(ret_val);
}
