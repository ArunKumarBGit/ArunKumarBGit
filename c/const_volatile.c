#include <stdio.h>

#define SUCCESS     0

int
main(void)
{
    static volatile const int i = 9;
    const int a;
    int *a_p = (int *)&a;
    int ret_val = SUCCESS;

    *a_p = 4;

    printf("static volatile const int i = '%d'\n"
           "const int a = '%d'\n\n", i, a);

    return(ret_val);
}
