#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main (void)
{
    char *str = NULL;
    char *str_const = "Juniper Networks HP";
    int ret_val = 0;

    str = (char *) malloc(100);

    printf("\n\nSizeof(int) = %ld, sizeof(long) = %ld\n\n", 
           sizeof(int), sizeof(long));
    
    printf("\n\nSizeof(str) = %ld, strlen(str) = %ld\n\n", 
           sizeof(str), strlen(str));
    printf("\n\nSizeof(str_const) = %ld, strlen(str_const) = %ld\n\n",
           sizeof(str_const), strlen(str_const));

    return(ret_val);
}
