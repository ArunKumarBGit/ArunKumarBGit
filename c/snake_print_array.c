#include <stdio.h>

#define SUCCESS             0
//#define printf(msg, ...)    printf("\n"msg"\n", ##__VA_ARGS__)
#define ROW                 4
#define COL                 4

void
snake_print (int arr[ROW][COL])
{
    int top_row = 0;
    int bot_row = ROW;
    int fst_col = 0;
    int lst_col = COL;
    int i       = 0;

    while ((top_row < bot_row) && (fst_col < lst_col)) {

        for (i = fst_col; i < lst_col; i++) {
            printf("%d ", arr[top_row][i]);
        }
        top_row++;

        for (i = top_row; i < bot_row; i++) {
            printf("%d ", arr[i][lst_col-1]);
        }
        lst_col--;

        if (top_row < bot_row) {
            for (i = lst_col - 1; i >= fst_col; i--) {
                printf("%d ", arr[bot_row-1][i]);
            }
            bot_row--;
        }

        if (fst_col < lst_col) {
            for (i = bot_row - 1; i >= top_row; i--) {
                printf("%d ", arr[i][fst_col]);
            }
            fst_col++;
        }
    }

    printf("\n\n");
}

int
main (void)
{
    int arr[ROW][COL] = {{ 1, 2, 3, 4},
                         {12,13,14, 5},
                         {11,16,15, 6},
                         {10, 9, 8, 7}};
    int ret_val = SUCCESS;

    snake_print(arr);

    return(ret_val);
}
