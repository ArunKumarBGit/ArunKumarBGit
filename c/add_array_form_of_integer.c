#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int*
addToArrayForm (int* num, int sz, int k, int* rt_sz)
{
    int temp_k = k;
    int len_k = 0;
    int len = 0;
    int *sum = NULL;
    int val_num = 0;
    int val_k = 0;
    int tot = 0;
    int carry = 0;
    int i = 0;
    int j = 0;
    int numj_used = 0;

    while (temp_k) {
        len_k++;
        temp_k /= 10;
    }

    len = (sz > len_k) ? sz : len_k;
    j = (sz < len_k) ? sz : len_k;

    *rt_sz = len;
    sum = (int *)malloc(*rt_sz * sizeof(int));

    for (i = len-1; i >= 0; i--) {
        if ((i < sz) && (numj_used == 0)) {
            val_num = num[i];
        } else if (j > 0) {
            numj_used = 1;
            val_num = num[--j];
        } else {
            val_num = 0;
        }

        if (k) {
            val_k = k % 10;
            k /= 10;
        } else {
            val_k = 0;
        }

        tot = val_num + val_k + carry;

        if (tot > 9) {
            sum[i] = tot % 10;
            carry = tot / 10;
        } else {
            sum[i] = tot;
            carry = 0;
        }
    }

    if (carry) {
        *rt_sz = len + 1;
        int *sum_nw = (int *)malloc(*rt_sz * sizeof(int));
        memcpy(sum_nw+1, sum, (len * sizeof(int)));
        sum_nw[0] = carry;

        free(sum);
        sum = sum_nw;
    }

    return(sum);
}


int
main (void)
{
    int num[] = {2, 1, 5};
    int k = 806;
    int sz = sizeof(num) / sizeof(num[0]);
    int *sum = NULL;
    int rt_sz = 0;
    int i = 0;

    sum = addToArrayForm (num, sz, k, &rt_sz);
    
    printf("\nrt_sz = %d\n\n", rt_sz);
    for (i = 0; i < rt_sz; i++) {
        printf("%d ", sum[i]);
    }
    printf("\n\n");

    return(0);
}
