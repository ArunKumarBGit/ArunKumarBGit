#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS     0

int
main(void)
{
    char str_lo[] = "abcd";
    int i = 0;
    int diff = 0;
    int ret_val = SUCCESS;

    printf("\nLower str = '%s', sizeof(str_lo) = '%ld'\n\n", 
           str_lo, sizeof(str_lo));

    for (i = 0; i < sizeof(str_lo) - 1; i++) {
        diff = str_lo[i] - 'a';
        str_lo[i] = 'A' + diff;
        printf("Upper char = '%c'\n", str_lo[i]);
    }

    printf("\nUpper str = '%s'\n\n", str_lo);

    return(ret_val);
}
