#include <stdio.h>

#define SUCCESS             0
#define printf(msg, ...)    printf("\n"msg"\n", ##__VA_ARGS__)

int
main (void)
{
    int ret_val = SUCCESS;

    return(ret_val);
}
