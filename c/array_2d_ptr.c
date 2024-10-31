#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int
main (void)
{
    char *str[] = {"ONE", "TWO", "THREE", "FOUR"};
    int num_pgs[][4] = {{3, 4}, {87, 24, 14}};

    printf("\n%s %s %s\n\n", *str, *(str + 1), (*(str + 2) + 2));

    printf("\nnum_pgs: %d %d %d\n\n", **num_pgs, *(*(num_pgs + 0) + 1), *(*(num_pgs + 1) + 1));

    /********************************/

    int **ptr_pp = NULL;
    int **needle_pp = NULL;
    int i = 0;
    int rows = 4;
    
    ptr_pp = (int **)malloc(rows * sizeof(int *));

    for (i = 0; i < rows; i++) {
        needle_pp = ptr_pp + i;

        *needle_pp = (int *)malloc(sizeof(int));
        **needle_pp = (i + 1) * 4;
    }

    for (i = 0; i < rows; i++) {
        printf("\n%d ", **(ptr_pp + i));
        free(*(ptr_pp + i));
    }
    printf("\n\n");

    free(ptr_pp);

    return(0);
}
