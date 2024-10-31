#include <stdio.h>

#define SUCCESS     0
#define scanf(msg)  printf("\n"msg"\n\n")

int
main (void)
{
    int ret_val = SUCCESS;

    scanf("Successfully made scanf to print this message :)");

    return(ret_val);
}
