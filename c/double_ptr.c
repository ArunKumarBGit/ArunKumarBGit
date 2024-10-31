#include <stdio.h>
#include <stdlib.h>

#define SUCCESS             0
//#define printf(msg, ...)    printf("\n"msg"\n", ##__VA_ARGS__)

int
main (void)
{
    int **arr = NULL;
    int **row_p = NULL;
    int *col_p = NULL;
    int row = 4;
    int col = 4;
    int i = 0;
    int j = 0;
    int ret_val = SUCCESS;

    arr = (int **)malloc(row * sizeof(int *));

    for (i = 0; i < row; i++) {
        row_p = arr + i;
        *row_p = (int *)malloc(col * sizeof(int));
        for (j = 0; j < col; j++) {
            col_p = *row_p + j;
            *col_p = (i+1) * (j+1);
        }
    }

    for (i = 0; i < row; i++) {
        printf("\n");
        for (j = 0; j < col; j++) {
            printf("%d ", *(*(arr + i) + j));
        }
        free(arr[i]);
    }
    free(arr);
    printf("\n\n");

    return(ret_val);
}
