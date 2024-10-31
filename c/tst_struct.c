#include <stdio.h>

typedef struct tst_ {
    int i;
    char c;
    float f;
} tst_t;

int
main (void)
{
    tst_t x = {9, 4};

    printf("\nx.f = '%f'\n\n", x.f);
    return(0);
}
