#include <stdio.h>

int
main (void)
{
    int arr[4] = {1, 2, 4};

    printf("\narr+2 = '%p', &arr[2] = '%p'\n"
           "*(arr+2) = '%d', arr[2] = '%d'\n"
           "arr[3] = '%d'\n\n", arr+2, &arr[2],
           *(arr+2), arr[2], arr[3]);
    return(0);
}
