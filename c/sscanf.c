#include <stdio.h>

#define SUCCESS             0
#define printf(msg, ...)    printf("\n"msg"\n", ##__VA_ARGS__)

int
main (void)
{
    char path[] = "transceiver:fc4/9";
    char pre_lc[50] = {0};
    char lc_slot_s[50] = {0};
    char post_lc[50] = {0};

    int ret_val = SUCCESS;

    sscanf(path, "%[^:]:%[^/]/%s", pre_lc, lc_slot_s, post_lc);

    printf("path = '%s', pre_lc = '%s', lc_slot_s = '%s', post_lc = '%s'\n",
           path, pre_lc, lc_slot_s, post_lc);

    return(ret_val);
}
