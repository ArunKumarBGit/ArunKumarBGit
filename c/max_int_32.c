#include <stdio.h>

#define SUCCESS             0
#define printf(msg, ...)    printf("\n"msg"\n", ##__VA_ARGS__)

int
main (void)
{
    int max_positive_num = 0x7FFFFFFF;
    unsigned int max_negative_num = 0xFFFFFFFF;
    int ret_val = SUCCESS;

    printf("max_positive_num = '%d'", max_positive_num);
    printf("max_negative_num = '%u'", max_negative_num);

    return(ret_val);
}
