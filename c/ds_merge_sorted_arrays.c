#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void 
merge (int* nums1, int m, int* nums2, int n)
{
    int *arr = NULL;
    int p1 = 0;
    int p2 = 0;
    int i = 0;
    
    if ((nums1 == NULL) || (nums2 == NULL) || (n == 0)) {
        return;
    }

    if (m == 0) {
        memcpy(nums1, nums2, (n * sizeof(int)));
        return;
    }
    
    arr = (int *)malloc((m+n) * sizeof(int));
    
    while (i < (m + n)) {
        
        if (p1 >= m) {
            arr[i++] = nums2[p2++];
            printf("\nDBG :: arr[%d] = '%d', p2 = '%d'", 
                   i-1, arr[i-1], p2-1);
            continue;
        }
        
        if (p2 >=  n) {
            arr[i++] = nums1[p1++];
            printf("\nDBG :: arr[%d] = '%d', p1 = '%d'", 
                   i-1, arr[i-1], p1-1);
            continue;
        }
        
        if (nums1[p1] <= nums2[p2]) {
            arr[i++] = nums1[p1++];
            printf("\nDBG :: arr[%d] = '%d', p1 = '%d'", 
                   i-1, arr[i-1], p1-1);
        } else {
            arr[i++] = nums2[p2++];
            printf("\nDBG :: arr[%d] = '%d', p2 = '%d'", 
                   i-1, arr[i-1], p2-1);
        }
    }
    
    memcpy(nums1, arr, (m+n) * sizeof(int));
    free(arr);
}

int
main (void)
{
    int nums1[] = {2, 0}; //{1, 2, 3, 0, 0, 0};
    int nums2[] = {1}; //{2, 5, 6};
    int m = 1; //3; 
    int n = 1; //3;
    int i = 0;

    printf("\n\nnums1 = {");
    for (i = 0; i < (m+n); i++) {
        printf("%d, ", nums1[i]);
    }
    printf("}\n");

    printf("\n\nnums2 = {");
    for (i = 0; i < n; i++) {
        printf("%d, ", nums2[i]);
    }
    printf("}\n");

    merge(nums1, m, nums2, n);

    printf("\n\nMerged array = {");
    for (i = 0; i < (m+n); i++) {
        printf("%d, ", nums1[i]);
    }
    printf("}\n\n");

    return(0);
}
