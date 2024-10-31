#include <stdio.h>

#define SUCCESS             0
//#define printf(msg, ...)    printf("\n"msg"\n", ##__VA_ARGS__)

/*
     1
    1 1
   1 2 1
  1 3 3 1
 1 4 6 4 1

 */

int
main (void)
{
    int row = 0;
    int col = 0;
    int space = 0;
    int pascal_num = 0;
    int num_row = 5;
    int ret_val = SUCCESS;

    printf("\n\n");
    for (row = 0; row < num_row; row++) {
        for (space = 0; space < (num_row - row); space++) {
            printf(" ");
        }
        
        pascal_num = 1;
        for (col = 0; col <= row; col++) {
            printf("%d ", pascal_num);
            pascal_num = pascal_num * (row - col)/(col + 1);
        }
        printf("\n");
    }
    printf("\n\n");

    return(ret_val);
}
