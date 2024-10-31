#include <stdio.h>
#include <stdlib.h>

#define MIN_ARGS        2
#define MASK_BYTE_0     0x000000FF
#define MASK_BYTE_1     0x0000FF00
#define MASK_BYTE_2     0x00FF0000
#define MASK_BYTE_3     0xFF000000
#define SHIFT_BYTE_0    24
#define SHIFT_BYTE_1    8
#define SHIFT_BYTE_2    8
#define SHIFT_BYTE_3    24

void
disp_syntax(void)
{
    printf("\nSyntax: <execute> <decimal network byte order "
            "32-bit number> <num-2> <num-3>...\n");
}


int
main (int argc, char *argv[])
{
    int i = 0;
    unsigned int num_n = 0;
    unsigned int num_h = 0;

    if (argc < MIN_ARGS) {
        disp_syntax();
    }

    for (i = 1; i < argc; i++) {
        num_n = atoi(argv[i]);
        num_h = (((num_n & MASK_BYTE_0) << SHIFT_BYTE_0) |
                 ((num_n & MASK_BYTE_1) << SHIFT_BYTE_1) |
                 ((num_n & MASK_BYTE_2) >> SHIFT_BYTE_2) |
                 ((num_n & MASK_BYTE_3) >> SHIFT_BYTE_3));
        printf("\nNumber in network byte order = '%d', '0x%x'"
               "\nNumber in host byte order    = '%d', '0x%x'\n",
               num_n, num_n, num_h, num_h);
    }
    printf("\n\n");

    return(0);
}
