#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int
main (void)
{
    int i = -13;
    int j = -14;
    unsigned int u = i % 2;
    int *ptr = (int *)100;
    char *c[3] = {"Hello", "World"};
    int *a[] = {&i, &j};
    int arr[] = {1, 2, 3, 4};

    printf("\ni = %d, u = %u\n\n", i, -13%2);
    printf("\nval = '%d'\n", ((64 >> (2 + 1 - 2)) & (~(1 << 2))) );

    ptr = ptr + 2;
    printf("\nptr = '%u'\n", (int)ptr);
    printf("\nsizeof(c) = '%lu'\n",sizeof(c));
    printf("\n(*a)[0] = '%d\n'", (*a)[0]);
    printf("\narr[0]++ = '%d'\n", ++arr[0]);

    return(0);
}
