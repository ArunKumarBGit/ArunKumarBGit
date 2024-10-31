#include <stdio.h>

#define SUCCESS             0
#define printf(msg, ...)    printf("\n"msg"\n", ##__VA_ARGS__)

int
main (void)
{
    char str[50];
    int ret_val = SUCCESS;

    printf("Enter string with space: ");
    scanf("%[^\n]", str);
    printf("Here's the string: %s", str);

    return(ret_val);
}
