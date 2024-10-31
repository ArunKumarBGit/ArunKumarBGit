#include <stdio.h>

#define SUCCESS             0
#define printf(msg, ...)    printf("\n"msg"\n", ##__VA_ARGS__)

int
main (void)
{
    int ret_val = SUCCESS;

    printf("5d = '%5d' 05d = '%05d'", 45, 45);

    return(ret_val);
}
