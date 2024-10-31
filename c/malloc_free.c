#include <stdio.h>
#include <stdlib.h>

int
main( )
{
    int *a_p = NULL;
    int *b_p = NULL;

    a_p = (int *)malloc(sizeof(int));

    *a_p = 9;
    printf("\na_p = '%p', *a_p = '%d'\n", a_p, *a_p);

    free(a_p);
    printf("\na_p = '%p', *a_p = '%d'\n", a_p, *a_p);

    return(0);
}
