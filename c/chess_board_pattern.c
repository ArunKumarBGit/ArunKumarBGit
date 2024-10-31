#include <stdio.h>

#define SUCCESS             0
#define printf(msg, ...)    printf(msg"\n", ##__VA_ARGS__)

int
main (void)
{
    static char odd_row[20];
    static char even_row[20];
    int n = 9;
    int i = 0;
    int ret_val = SUCCESS;

    for (i = 0; i < n; i++) {
        if (i & 0x1) {
            odd_row[i] = 'W'; 
            even_row[i] = 'B';
        } else {
            odd_row[i] = 'B';
            even_row[i] = 'W';
        }
    }

    for (i = 0; i < n; i++) {
        if (i & 0x1) {
            printf("%s", even_row);
        } else {
            printf("%s", odd_row);
        }
    }

    return(ret_val);
}
