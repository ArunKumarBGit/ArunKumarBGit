#include <stdio.h>
#include <strings.h>

#define STR_SZ  33 // including NULL termination

int
dec_to_bin_arithmetic (unsigned int num)
{
    int i = 0;
    unsigned char mod = 0;
    char bin[STR_SZ];

    memset(bin, '0', sizeof(bin));
    bin[STR_SZ-1] = '\0';

    if (num == 0) {
        printf("\n\nBinary value = %s b\n\n", bin);
        return(0);
    }

    i = STR_SZ - 2;

    while ((num > 0) && (i >= 0)) {
        mod = num % 2;
        num /= 2;

        if (mod == 1) {
            bin[i] = '1';
        }
        i--;
    }

    printf("\n\nBinary value = %s b\n\n", bin);

    return(0);
}

int
dec_to_bin_bitwise (unsigned int num)
{
    int i = 0;
    unsigned char mod = 0;

    printf("\n\n[Optimized] Binary value = ");

    for (i = 31; i >= 0; i--) {
        mod = (num >> i) & 0x1;
        printf("%d", mod);
    }

    printf(" b\n\n");

    return(0);
}

int
main(void)
{
    unsigned int num = 0xABCDABCD;

    dec_to_bin_arithmetic(num);
    dec_to_bin_bitwise(num);

    return(0);
}
