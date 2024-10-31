#include <stdio.h>

#define SUCCESS             0
//#define printf(msg, ...)    printf("\n"msg"\n", ##__VA_ARGS__)

int
main (void)
{
    int i = 0;
    int j = 0;
    int n = 5;
    int ret_val = SUCCESS;

    printf("\n\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if ((i == 1) || (i == n)) {
                printf("* ");
            } else {
                printf("%c ", ((j == 1) || (j == n))? '*' : ' ');
            }
        }
        printf("\n");
    }
    printf("\n\n");

    return(ret_val);
}
