#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* 
twoSum(int* nums, int numsSize, int target, int* returnSize)
{
//#if 0
    if ((nums == NULL) || (numsSize == 0) || (returnSize == NULL)) {
        return(NULL);
        printf("Returnined here\n");
    }
//#endif
    
    for (int i = 0; i < numsSize; i++) {
        for (int j = i+1; j < numsSize; j++) {
            printf("nums[i] = '%d', nums[j] = '%d', target = '%d'\n",
                   nums[i], nums[j], target);
            if ((nums[i] + nums[j]) == target) {
                int *ans_p = (int *) malloc(2 * sizeof(int));
                *ans_p = i;
                *(ans_p + 1) = j;
                //ans_p[0] = i;
                //ans_p[1] = j;
                *returnSize = 2;
                printf("%d, %d\n", ans_p[0], ans_p[1]);
                return(ans_p);
            } else {
                printf("Else :: nums[%d] (%d) + nums[%d] (%d) = '%d', target = '%d'\n",
                       i, nums[i], j, nums[j], nums[i] + nums[j], target);
            }
        }
        
    }
    
    return(NULL);

}

int
main (void)
{
    int arr[] = {2, 7, 11, 15};
    int rtn_sz = 0;

    int *index_p = twoSum(arr, (sizeof(arr)/ sizeof(arr[0])), 9, &rtn_sz);
    free(index_p);

    return(0);
}
