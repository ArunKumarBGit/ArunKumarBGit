#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int*
plusOne(int* digits, int digitsSize, int* returnSize)
{
    unsigned long int num = 0;
    int *res_arr = NULL;
    int i = 0;

    if ((digits == NULL) || (returnSize == NULL)) {
        printf("Invalid parameter\n");
        return NULL;
    }

    *returnSize = digitsSize;
    res_arr = (int *) malloc(*returnSize * sizeof(int));
    memcpy(res_arr, digits, (*returnSize * sizeof(int)));

    for (i = *returnSize - 1; i >= 0; i--) {
        if (res_arr[i] < 9) {
            res_arr[i]++;
            break;
        } else {
            res_arr[i] = 0;
        }
    }

    if (i == -1) {
        *returnSize += 1;
        res_arr = (int *) realloc(res_arr, (*returnSize * sizeof(int)));
        memset(res_arr, 0, (*returnSize * sizeof(int)));
        res_arr[0] = 1;
    }

    return(res_arr);
}

int
main (void)
{
    //int digits[] = {1, 2, 3};
    int digits[] =
    {7,2,8,5,0,9,1,2,9,5,3,6,6,7,3,2,8,4,3,7,9,5,7,7,4,7,4,9,4,7,0,1,1,1,7,4,0,0,6};

    int sz = sizeof(digits)/ sizeof(digits[0]);
    int rtn_sz = 0;
    int i = 0;
    int *arr = NULL;

    arr = plusOne(digits, sz, &rtn_sz);

    printf("\n");
    for (i = 0; i < rtn_sz; i++) {
        printf("%d, ", arr[i]);
    }
    printf("\n\n");
}
