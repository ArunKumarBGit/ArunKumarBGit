#include <stdio.h>

int 
getSum (int a, int b)
{
    int carry = 0;
    
    while (b) {
        carry = a & b;
        a = a ^ b;
        b = (unsigned)carry << 1;
        
    }
    
    return(a);
}

int
main (void)
{
    int a = 4;
    int b = 5;

    printf("\n\nSum of '%d' and '%d' = '%d'\n\n",
           a, b, getSum(a, b));

    return(0);
}
