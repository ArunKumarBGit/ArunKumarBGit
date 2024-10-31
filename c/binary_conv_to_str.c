#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// 5 --> "00000000000000000000000000000101"
const char * 
convert_to_binary_format (uint32_t x)
{
    char *bin_str_p = NULL;
    char bin = 0;
    uint32_t sz = (8 * sizeof(uint32_t));
    int i = 0;

    bin_str_p = (char *)malloc(sz+1);
    memset(bin_str_p, 0, sz+1);

    if (x == 0) {
        bin_str_p[sz] = '0';
        return(bin_str_p);
    }

    for (i = sz-1; i >= 0; i--) {
        if (x & 0x1) {
            bin_str_p[i] = '1';
        } else {
            bin_str_p[i] = '0';
        }

        x >>= 1;
    }

    return(bin_str_p);
}


int
main (void)
{
    const char *p = convert_to_binary_format(5); //(1 << 31);
    printf("%s\n", p);
    free((void *)p);
}

#if 0

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
    uint32_t i = *(int *)c;

    if (i == 1) {
        return(TRUE);
    }

    return(FALSE);

}
#endif
