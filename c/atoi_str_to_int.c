#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS     0

int
my_atoi (const char *str)
{
    int num = 0;
    int sign = 1;
    int i = 0;

    if (str == NULL) {
        return(num);
    }

    if (str[0] == '-') {
        sign = -1;
        i++;
    }

    while (str[i] != '\0') {
        num = (num * 10) + (str[i] - '0');
        i++;
    }

    return(num * sign);
}

int
main (void)
{
    char str[] = "0459";
    int ret_val = SUCCESS;

    printf("\nstr = '%s', num = '%d'\n\n", str, my_atoi(str));

    return(ret_val);
}
