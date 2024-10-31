#include <stdio.h>
#include <string.h>

#define SUCCESS             0
//#define printf(msg, ...)    printf("\n"msg"\n", ##__VA_ARGS__)

int
main (void)
{
    char str[100]   = "Test string to reverse";
    char str_cpy[100];
    char *ptr[20];
    int cnt         = 0;
    int i           = 0;
    int ret_val     = SUCCESS;

    strcpy(str_cpy, str);

    ptr[cnt] = strtok(str_cpy, " ");
    
    while (ptr[cnt] != NULL) {
        ptr[++cnt] = strtok(NULL, " ");
    }

    printf("\n%s\n", str);
    for (i = cnt-1; i >= 0; i--) {
        printf("%s ", ptr[i]);
    }
    printf("\n");

    return(ret_val);
}
