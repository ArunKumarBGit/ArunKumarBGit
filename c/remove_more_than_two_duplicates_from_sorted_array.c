#include <stdio.h>

void
shift_array_elements (int *nums, int index_lo, int index_hi)
{
    int i = 0;
    int rst_val = -99;
    
    for (i = index_lo; i < index_hi-1; i++) {
        nums[i] = nums[i+1];
    }
    
    nums[index_hi-1] = -99;
}

int
removeDuplicates (int* nums, int sz)
{
    int i           = 0;
    int j           = 0;
    int nw_sz       = sz;
    int rpt_cnt     = 0;
    
    if (nums == NULL) {
        return(0);
    }
    
    for (i = 0; i < nw_sz; i++) {

        rpt_cnt = 1;
        
        for (j = i+1; j < nw_sz; j++) {
            if ((nums[i] == nums[j]) && (rpt_cnt <= 1)) {
                rpt_cnt++;
                continue;
            } else if ((nums[i] == nums[j]) && (rpt_cnt >= 2)) {
                shift_array_elements(nums, j, nw_sz);
                nw_sz--;
                j--; // Recheck shifted elements
                continue;
            } else if (nums[i] != nums[j]) {
                break;
            }
        } // j
    } // i
    
    return(nw_sz);
}

int
main (void)
{
    int arr[]   = {0, 0, 1, 1, 1, 1, 2, 3, 3};
    int sz      = sizeof(arr)/ sizeof(arr[0]);
    int i       = 0;

    printf("\n\nOriginal array: ");
    for(i = 0; i < sz; i++) {
        printf("%d ", arr[i]);
    }

    sz = removeDuplicates(arr, sz);
    printf("\n\nAfter removing more than 2 duplicates, \narray: ");
    for(i = 0; i < sz; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    return(0);
}
