#include <stdio.h>
#include <stdlib.h>

#define MIN_ARGS        2
#define MASK_BYTE_0     0x00000000000000FF
#define MASK_BYTE_1     0x000000000000FF00
#define MASK_BYTE_2     0x0000000000FF0000
#define MASK_BYTE_3     0x00000000FF000000
#define MASK_BYTE_4     0x000000FF00000000
#define MASK_BYTE_5     0x0000FF0000000000
#define MASK_BYTE_6     0x00FF000000000000
#define MASK_BYTE_7     0xFF00000000000000
#define SHIFT_BYTE_0    56
#define SHIFT_BYTE_1    40
#define SHIFT_BYTE_2    24
#define SHIFT_BYTE_3    8
#define SHIFT_BYTE_4    8
#define SHIFT_BYTE_5    24
#define SHIFT_BYTE_6    40
#define SHIFT_BYTE_7    56

void
disp_syntax(void)
{
    printf("\nSyntax: <execute> <decimal network byte order "
            "64-bit number> <num-2> <num-3>...\n");
}


void
ntoh64 (int argc, char *argv[])
{
    int i = 0;
    unsigned long long int num_n = 0;
    unsigned long long int num_h = 0;

    for (i = 1; i < argc; i++) {
        num_n = atoll(argv[i]);
        num_h = (((num_n & MASK_BYTE_0) << SHIFT_BYTE_0)    |
                 ((num_n & MASK_BYTE_1) << SHIFT_BYTE_1)    |
                 ((num_n & MASK_BYTE_2) << SHIFT_BYTE_2)    |
                 ((num_n & MASK_BYTE_3) << SHIFT_BYTE_3)    |
                 ((num_n & MASK_BYTE_4) >> SHIFT_BYTE_4)    |
                 ((num_n & MASK_BYTE_5) >> SHIFT_BYTE_5)    |
                 ((num_n & MASK_BYTE_6) >> SHIFT_BYTE_6)    |
                 ((num_n & MASK_BYTE_7) >> SHIFT_BYTE_7));
        printf("\nNumber in network byte order = '%llu', '0x%llx'"
               "\nNumber in host byte order    = '%llu', '0x%llx'\n",
               num_n, num_n, num_h, num_h);
    }
    printf("\n\n");
}

int
main (int argc, char *argv[])
{
    if (argc < MIN_ARGS) {
        disp_syntax();
    }

    ntoh64(argc, argv);

    return(0);
}
