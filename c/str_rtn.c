#include <stdio.h>

#define SUCCESS             0
#define printf(msg, ...)    printf("\n"msg"\n", ##__VA_ARGS__)

char *
str_rtn(void) {
    char *str = "Working!";

    return(str);
}

int
main (void)
{
    int ret_val = SUCCESS;

    printf("%s", str_rtn());

    return(ret_val);
}
