#include <stdio.h>

int
main (void)
{
    int i = 0;
    int cnt = 10;

    for (i = 0; i < cnt; i++) {
        printf("\n\ni = '%d', cnt = '%d'\n", i, cnt--);
    }

    return(0);
}
