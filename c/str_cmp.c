#include <stdio.h>
#include <string.h>

#define SUCCESS             0
#define printf(msg, ...)    printf("\n"msg"\n", ##__VA_ARGS__)

int
main (void)
{
    char *str_1 = "transceiver_peer";
    char str_2[] = "transceiver_peer";
    int ret_val = SUCCESS;

    if (!strncmp(str_1, str_2, 32)) {
        printf("Both strings match '%s'", str_1);
    } else {
        printf("Didn't match");
    }

    return(ret_val);
}
