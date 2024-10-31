#include <stdio.h>
#include <math.h>

#define SUCCESS                     0
//#define printf(msg, ...)    printf("\n"msg"\n", ##__VA_ARGS__)
#define printf(format, args...)     printf("\n"format"\n", ##args)

void
print_roundoff_val (double val, int dec)
{
    printf("val = %-20.4f", val);
}


double
roundoff_val (double val, int dec)
{
    double round_val    = 0;
    int conv_factor     = 1;
    double round_num    = 0.5;
    //int i               = 0;

    //for (i = 0; i < dec; i++) {
    //    conv_factor *= 10;
    //}

    conv_factor = pow(10, dec);

    round_val = (int)((val * conv_factor) + round_num);
    round_val /= conv_factor;

    return(round_val);
}


int
main (void)
{
    double val = 49.666666;
    int ret_val = SUCCESS;

    print_roundoff_val(val, 4);
    printf("Roundoff val = '%f'", roundoff_val(val, 4));

    return(ret_val);
}
