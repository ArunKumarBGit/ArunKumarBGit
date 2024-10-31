#include <stdio.h>
#include <string.h>

#define SUCCESS             0
#define printf(msg, ...)    printf("\n"msg"\n", ##__VA_ARGS__)

int
main (void)
{
    char str1[] = "";
    char str2[] = "\0";
    int ret_val = SUCCESS;

    printf("str1 = '%s', len = '%ld', str2 = '%s', len = '%ld'", 
            str1, strlen(str1), str2, strlen(str2));

    return(ret_val);
}
