#include <stdio.h>

int
main (void)
{
    unsigned char arr[256] = {0xA1, 
                             [1]            = 0xA2,
                             [2 ... 0xFE]   = 0xA3,
                             [0xFF]         = 0xA4};

    printf("arr[0] = '0x%x', arr[1] = '0x%x', arr[49] = '0x%x', "
           "arr[255] = '0x%X'\n",
           arr[0], arr[1], arr[49], arr[255]);

    printf("sizeof(arr) = '%ld', sizeof(&arr) = '%ld', \n"
           "sizeof(arr[0]) = '%ld', sizeof(&arr[0]) '%ld'\n",
           sizeof(arr), sizeof(&arr), sizeof(arr[0]), sizeof(&arr[0]));

    printf("&arr = '%p', &arr[0] = '%p', &arr[1] = '0x%x'\n",
           (void *)&arr, (void *)&arr[0], (unsigned int)&arr[1]);

    return(0);
}
