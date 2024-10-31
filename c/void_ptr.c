#include <stdio.h>

#define SUCCESS             0
//#define printf(msg, ...)    printf("\n"msg"\n", ##__VA_ARGS__)
#define printf(format, args...)    printf("\n"format"\n", ##args)

int
main (void)
{
    void *v_p   = NULL;
    int *i_p    = NULL;
    int i       = 0;
    int ret_val = SUCCESS;

    i_p = &i;
    v_p = i_p;

    return(ret_val);
}
