#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS     0

void
prnt_rev_bits (unsigned int num)
{
    int num_bits = sizeof(num) * 8;
    unsigned int rev_num = 0;
    int i = 0;

    for (i = 0; i < num_bits - 1; i++) {
        if (num & (1 << i)) {
            rev_num |= (1 << (num_bits-1-i));
        }
    }

    printf("\nGiven num     = '0x%x',\nrev_num = '0x%x'\n\n",
           num, rev_num);

}

int
main (void)
{
    int ret_val = SUCCESS;

    prnt_rev_bits(0x03);

    return(ret_val);
}
