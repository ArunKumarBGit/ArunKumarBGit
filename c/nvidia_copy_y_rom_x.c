//x, y
//x {bit-4 to bit-6}   --> y {bit-12 to bit-14}

#include <stdion.h>

#define MASK_BIT_4_to_6     0x0070
#define MASK_BIT_12_to_14   0x7000

int
populate_y_from_x (unsigned int x, unsigned int *y_p)
{
    unsigned int temp = 0;

    temp = (x & MASK_BIT_4_to_6);

    *y_p &= ~(MASK_BIT_12_to_14);
    
    *y_p |= (temp << 8);

    return(0);
}

int
main (void)
{
    unsigned int x = 0;
    unsigned int y = 0;

    populate_y_from_x(x, &y);

    return(0);
}
