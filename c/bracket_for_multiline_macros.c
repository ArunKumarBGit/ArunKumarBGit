#include <stdio.h>

#define SUCCESS     0

int
main (void)
{
    int ret_val = SUCCESS;

    ({printf("\nBracket enclosure ");
     printf("works good\n\n");});

    return(ret_val);
}
