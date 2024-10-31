#include <stdio.h>
#include <stdlib.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** 
generate (int numRows, int* rt_sz, int** rt_col_sz)
{
    int **pas_tri = NULL;
    int **row_pp = NULL;
    int *col_p = NULL;
    int *col_sz_p = NULL;
    int i = 0;
    int j = 0;
    int pas_num = 1;
    
    if (rt_sz == NULL) {
        printf("Invalid parameter\n");
        return (NULL);
    }
    
    pas_tri = (int **) malloc(numRows * sizeof(int *));
    *rt_col_sz = (int *) malloc(numRows * sizeof(int ));
    *rt_sz = numRows;
    
    for (i = 0; i < numRows; i++) {
        col_sz_p = *rt_col_sz + i;
        *col_sz_p = i + 1;
                
        row_pp = pas_tri + i;
        *row_pp = (int *) malloc((i + 1) * sizeof(int));
        
        pas_num = 1;
        for (j = 0; j <= i; j++) {
            col_p = *row_pp + j;
            *col_p = pas_num;
            pas_num = pas_num * (i - j) / (j + 1);
        }
    }
    
    return(pas_tri);
}

int
main (void)
{
    int sz = 0;
    int rows = 9;
    int *col_sz = NULL;
    int **arr = NULL;
    int i = 0;
    int j = 0;

    arr = generate(rows, &sz, &col_sz);

    for (i = 0; i < rows; i++) {
        printf("\n");
        for (j = 0; j < (rows - i); j++) {
            printf(" ");
        }

        for (j = 0; j < /*(i+1)*/ *(col_sz + i); j++) {
            printf("%d ", arr[i][j]);
        }
    }
    printf("\n\n");

    return(0);
}
