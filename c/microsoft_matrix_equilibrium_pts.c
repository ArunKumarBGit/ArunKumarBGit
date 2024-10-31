// https://app.codility.com

/*
 * Example test:   
 *  [[2, 7, 5], [3, 1, 1], [2, 1, -7], [0, 2, 1], [1, 6, 8]] -->  2 (1,1), (3,1)
 *  [[1, 2, 1], [0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0]]  -->  1
 *  [[0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0]]  --> 15
 * 
 * A pair (row, col) is called an equilibrium point of Matrix, i the following
 * conditions are met:
 *  . 0 <= row < max_row
 *  . 0 <= col < max_col
 *  . The sum of elements in rows above the given 'row' is equal to the sum of
 *    sum of elements in rows below the given 'row'
 *  . The sum of elements in columns to the left of the given 'col' is equal to
 *    the sum of elements in columns to the right of the given 'col'
 * 
 */
#define SUCCESS             0
#define INVALID_PARAM       -1

int
get_sum_of_rows (int **arr, int max_row, int max_col, 
                int row_index, int *row_lo_sum_p, int *row_hi_sum_p)
{
    int i = 0;
    int j = 0;

    // Parameters validity check
    if (arr == NULL) {
        printf("Error :: Invalid parameter passed\n");
        return(INVALID_PARAM);
    }

    // Initialize
    *row_lo_sum_p = 0;
    *row_hi_sum_p = 0;

    // Lower row sum
    for (i = 0; i < row_index; i++) {
        for (j = 0; j < max_col; j++) {
            *row_lo_sum_p += arr[i][j];
        }
    }

    // Higher row sum
    for (i = row_index+1; i < max_row; i++) {
        for (j = 0; j < max_col; j++) {
            *row_hi_sum_p += arr[i][j];
        }
    }

    return(SUCCESS);
}

int
get_sum_of_cols (int **arr, int max_row, int max_col, 
                int col_index, int *col_lo_sum_p, int *col_hi_sum_p)
{
    int i = 0;
    int j = 0;

    // Parameters validity check
    if (arr == NULL) {
        printf("Error :: Invalid parameter passed\n");
        return(INVALID_PARAM);
    }

    // Initialize
    *col_lo_sum_p = 0;
    *col_hi_sum_p = 0;

    // Lower column sum
    for (i = 0; i < max_row; i++) {
        for (j = 0; j < col_index; j++) {
            *col_lo_sum_p += arr[i][j];
        }
    }

    // Higher column sum
    for (i = 0; i < max_row; i++) {
        for (j = col_index+1; j < max_col; j++) {
            *col_hi_sum_p += arr[i][j];
        }
    }

    return(SUCCESS);
}

int
solution (int **A, int N, int M) 
{
    int num_equ_pts = 0;
    int row_idx = 0;
    int col_idx = 0;
    int row_lo_sum = 0;
    int row_hi_sum = 0;
    int col_lo_sum = 0;
    int col_hi_sum = 0;
    int ret_val = SUCCESS;

    // Parameters validity check
    if ((A == NULL) || (N <= 0) || (M <= 0)) {
        printf("Error :: Invalid parameter passed\n");
        return(INVALID_PARAM);
    }

    // Identify equilibrium points
    for (row_idx = 0; row_idx < N; row_idx++) {
        for (col_idx = 0; col_idx < M; col_idx++) {
            ret_val = get_sum_of_rows(A, N, M, row_idx, &row_lo_sum, &row_hi_sum);
            if (ret_val != SUCCESS) {
                printf("Error :: Failed to compute sum of rows, row_idx = '%d', col_idx = '%d', "
                       "row_lo_sum = '%d', row_hi_sum = '%d', ret_val = '%d'", 
                       row_idx, col_idx, row_lo_sum, row_hi_sum, ret_val);
                return(ret_val);
            }

            ret_val = get_sum_of_cols(A, N, M, col_idx, &col_lo_sum, &col_hi_sum);
            if (ret_val != SUCCESS) {
                printf("Error :: Failed to compute sum of columns, row_idx = '%d', col_idx = '%d', "
                       "col_lo_sum = '%d', col_hi_sum = '%d', ret_val = '%d'", 
                       row_idx, col_idx, col_lo_sum, col_hi_sum, ret_val);
                return(ret_val);
            }

            // Equilibrium condition check
            if ((row_lo_sum == row_hi_sum) && (col_lo_sum == col_hi_sum)) {
                num_equ_pts++;
            }
        }
    }

    return(num_equ_pts);
}

