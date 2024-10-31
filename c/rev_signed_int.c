#include <stdio.h>


int 
reverse (int x) 
{
    int max_neg = 0x80000000;
    int max_pos = 0x7FFFFFFF;
    char sign = 1;
    int rev_x = 0;
    
    if (x == max_neg) {
        return(0);
    }
    
    if (x < 0) {
        sign = -1;
        x *= sign;
    }
    
    while (x) {
        if ((max_pos/10) < rev_x) {
            return(0);
        } else if (((max_pos/10) == rev_x) && 
                    ((max_pos % 10) < (x % 10))) {
            return(0);
        }
        
        rev_x = (rev_x * 10) + (x % 10);
        x /= 10;
    }
    
    return(sign * rev_x);
}

int
main (void)
{
    int x = -149;

    printf("\n\nx = '%d', rev_x = '%d'\n\n", x, reverse(x));

    return(0);
}
