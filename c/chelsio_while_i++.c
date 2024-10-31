#include <stdio.h>

int
main (void)
{
    //int i = 1;
    int i = 2147483636;
    char once = 0;

    while (i++) {
        printf("i = '%d'\n", i);

        if ((i < 0) && (once == 0)) {
            i = -4;
            once = 1;
        }
    }

    return(0);
}
