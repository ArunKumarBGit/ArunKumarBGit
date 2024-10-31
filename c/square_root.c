#include <stdio.h>
#include <math.h>

#define SUCCESS             0
#define printf(msg, ...)    printf("\n"msg"\n", ##__VA_ARGS__)

double
my_sqrt(double num)
{
    double start = 0;
    double end = num;
    double mid = 0;
    double sqrt = 0;
    int i = 0;
    double inc = 0;

    while (start <= end) {

        mid = (start + end)/2;

        if ((mid * mid) == num) {
            sqrt = mid;
            break;
        } else if ((mid * mid) < num) {
            sqrt = start;
            start = mid + 1;
        } else if ((mid * mid) > num) {
            end = mid - 1;
        }
    }

    inc = 0.1;
    for (i = 0; i < 5; i++) {
        while ((sqrt * sqrt) <= num) {
            sqrt += inc;
        }

        sqrt -= inc;
        inc /= 10;
    }

    return(sqrt);
}

int
main (void)
{
    float num = 2;
    int ret_val = SUCCESS;

    printf("Sqare root of '%f' = '%5.4f', '%5.4f'\n", 
           num, my_sqrt(num), sqrt(num));

    return(ret_val);
}
