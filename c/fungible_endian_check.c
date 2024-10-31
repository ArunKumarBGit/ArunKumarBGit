#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define TRUE    1
#define FALSE   0

// Endian
typedef union endian_uni_ {
    uint32_t i;
    char c;
} endian_uni_t;

bool
is_little_endian(void)
{
    endian_uni_t uni;

    uni.i = 1;

    if (uni.c == 1) {
        return(TRUE);
    }

    return(FALSE);
}


bool
is_big_endian(void)
{
    char c[4] = {0, 0, 0, 1};
    uint32_t i = *(uint32_t *)c;

    printf("\tDBG :: i = 0x%x\n", i);
    if (i == 1) {
        return(TRUE);
    }

    return(FALSE);
}

int
main (void)
{
    printf("is_little_endian = '%s'\n\n",
           is_little_endian() ? "TRUE" : "FALSE");

    printf("is_big_endian = '%s'\n\n",
           is_big_endian() ? "TRUE" : "FALSE");

    return(0);
}
