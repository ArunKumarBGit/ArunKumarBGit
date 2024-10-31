#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void
shift_array (int *arr, int index_lo, int index_hi)
{
    int i = 0;

    for (i = index_lo; i < index_hi-1; i++) {
        arr[i] = arr[i+1];
    }
    arr[index_hi-1] = -99;
}

int
removeDuplicates (int* nums, int numsSize)
{
    int i = 0;
    int j = 0;
    int nw_sz = numsSize;

    if (nums == NULL) {
        return(0);
    }

    for (i = 0; i < nw_sz; i++) {
        for (j = i+1; j < nw_sz; j++) {
            if (nums[i] == nums[j]) {
                shift_array(nums, j, nw_sz);
                j--;    // Revalidated from the shifted location
                nw_sz--;
                continue;
            }
            break;
        }
    }
    return(nw_sz);
}

int
main (void)
{
    int arr[] = {0,0,1,1,1,2,2,3,3,4};
    int sz = sizeof(arr)/ sizeof(arr[0]);
    int i = 0;

    printf("\nBefore removing duplicates, size = '%d'\n", sz);

    printf("\nArray = [");
    for (i = 0; i < sz; i++) {
        printf("%d, ", arr[i]);
    }
    printf("]\n\n");

    sz = removeDuplicates(arr, sz);

    printf("\nAfter removing duplicates, size = '%d'\n", sz);

    printf("\nArray = [");
    for (i = 0; i < sz; i++) {
        printf("%d, ", arr[i]);
    }
    printf("]\n\n\n");

    return(0);
}
