#include <stdio.h>

#define SUCCESS         0
#define MY_SIZEOF(num)  ((char *)(&num + 1) - ((char *)&num))

int
main (void)
{
    int i = 0;
    char c = 0;
    int ret_val = SUCCESS;

    printf("\nMY_SIZEOF(i) = '%ld', MY_SIZEOF(c) = '%ld'\n",
           MY_SIZEOF(i), MY_SIZEOF(c));

    return(ret_val);
}
