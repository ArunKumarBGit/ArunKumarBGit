#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS     0

void
print_2s_complement_v1 (int num) 
{
    printf("\nV1 :: num = '%d', 2s complement = '%d'\n",
           num, ((~num) + 1));
}

void
print_2s_complement_v2 (int num) 
{
    printf("\nV2 :: num = '%d', 2s complement = '%d'\n",
           num, -num);
}

int
main(void)
{
    int ret_val = SUCCESS;

    print_2s_complement_v1(-9);
    print_2s_complement_v2(4);
    print_2s_complement_v2(-49);

    return(ret_val);
}
