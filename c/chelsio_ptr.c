#include <stdio.h>

int
main (void)
{
    int *i = (int *)100;
    i++;

    printf("\n i = '%d'\n\n", (int)i);

    return(0);
}
