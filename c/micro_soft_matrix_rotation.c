#include <stdio.h>

#define ROW     3
#define COL     3

int
main (void)
{
    int arr[ROW][COL] = {{1, 2, 3},
                         {4, 5, 6},
                         {7, 8, 9}};
    int row = 0;
    int col = 0;

    printf("\n");
    // Regular array
    for (row = 0; row < ROW; row++) {
        for (col = 0; col < COL; col++) {
            printf("%d ", arr[row][col]);
        }
        printf("\n");
    }
    printf("\n\n");

    // 90 degree rotation code
    for (col = 0; col < COL; col++) {
        for (row = ROW-1; row >= 0; row--) {
            printf("%d ", arr[row][col]);
        }
        printf("\n");
    }
    printf("\n\n");

    return(0);
}
