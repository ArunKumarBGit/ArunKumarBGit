#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 5 --> "101"
char* 
convert_to_binary_format(uint32_t x)
{
    char *bin_str_p = NULL;
    char bin = 0;
    uint32_t sz = (8 * sizeof(uint32_t));
    int32_t i = 0;

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
    int num     = 0x49;
    char *str_p = NULL;

    str_p = convert_to_binary_format(num);
    if (str_p != NULL) {
        printf("num = '0x%x', str_p = '%s'\n\n", num, str_p);
        free(str_p);
    }

    return(0);
}
