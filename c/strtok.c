#include <stdio.h>
#include <string.h>

#define SUCCESS             0
#define printf(msg, ...)    printf("\n"msg"\n", ##__VA_ARGS__)

int
main (void)
{
    char str[] = "Test string one";
    char *str_p = NULL;
    int ret_val = SUCCESS;

    printf("Before strtok :: str = '%s', len = '%ld'", 
            str, strlen(str));
    str_p = strtok(str, " ");

    while (str_p != NULL) {
        printf("str_p = '%s'", str_p);

        str_p = strtok(NULL, " ");
    }

    printf("After strtok :: str = '%s', len = '%ld'", 
            str, strlen(str));

    return(ret_val);
}
