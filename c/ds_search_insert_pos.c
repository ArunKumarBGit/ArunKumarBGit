#include <stdio.h>
#include <stdlib.h>

int 
searchInsert (int* nums, int sz, int target)
{
    int start = 0;
    int end = sz - 1;
    int mid = 0;
    
    if (nums == NULL) {
        return(0);
    }
    
    if (target > nums[sz-1]) {
        return(sz);
    }
    
    if (target < nums[0]) {
        return(0);
    }
    
    while (start <= end) {
        
        mid = (start + end) / 2;
        
        if (target > nums[mid]) {
            start = mid + 1;
        } else if (target < nums[mid]) {
            end = mid - 1;
        } else if (target == nums[mid]) {
            return(mid);
        }
    }
    
    return(end + 1);
}

int
main (void)
{
    int arr[] = {-4, 0, 4, 5, 14};
    int target = 9;
    int sz = (sizeof(arr)/sizeof(arr[0]));
    int i = 0;

    printf("\n\nArray = {");

    for (i = 0; i < sz; i++) {
        printf("%d, ", arr[i]);
    }
    printf("}\n\n");
    printf("Found/ insert '%d' in index '%d'\n\n", target,
            searchInsert(arr, (sizeof(arr)/sizeof(arr[0])), target));

    return(0);
}
