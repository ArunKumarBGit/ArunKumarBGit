#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS     0
#define TRUE        1
#define FALSE       0

int 
isPowerof2 (int x)
{
    return (x && !(x & x-1));
}

int
isPowerof2_detailed (int x)
{
    if (x <= 0) {
        printf("Invalid parameter '%d'\n", x);
        return (FALSE);
    } else if (!(x & (x-1))) {
        printf("\nTRUE :: '%d' is power of 2\n", x);
        return (TRUE);
    } else {
        return (FALSE);
        printf("\nFALSE :: '%d' is _NOT_ power of 2\n", x);
    }
}

int
main(void)
{
    int ret_val = SUCCESS;

    isPowerof2_detailed(16);

    return(ret_val);
}
