#include <stdio.h>

#define SUCCESS             0
#define printf(msg, ...)    printf("\n"msg"\n", ##__VA_ARGS__)

int
main (void)
{
    unsigned int num = 1;
    int ret_val = SUCCESS;

    printf("num = '0x%x', num << 31 = '0x%x'", num, num << 31);

    if (5 < 5) {
        printf("Less");
    } else if (5 > 5) {
        printf("Great");
    } else if (5 == 5) {
        printf("Equal");
    }

    return(ret_val);
}
