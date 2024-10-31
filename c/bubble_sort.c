#include <stdio.h>

#define SUCCESS             0
#define printf(msg, ...)    printf("\n"msg"\n", ##__VA_ARGS__)

void
swap (int *a_p, int *b_p)
{
    *a_p += *b_p;
    *b_p = *a_p - *b_p;
    *a_p = *a_p - *b_p;
}

void
bubble_sort (int arr[], int cnt)
{
    int i = 0;
    int j = 0;
    int loop_cnt = 0;
    int is_swapped = 0;

    for (i = 0; i < cnt - 1; i++) {
        is_swapped = 0;
        for (j = 0; j < cnt - 1 - i; j++) {
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
                is_swapped = 1;
                loop_cnt++;
            }
        }

        if (!is_swapped) {
            break;
        }
    }

    printf("loop_cnt = '%d'", loop_cnt);
}

void
print_arr (int arr[], int cnt)
{
    int i = 0;

    for (i = 0; i < cnt; i++) {
        printf("arr[%d] = '%d'", i, arr[i]);
    }
}

int
main (void)
{
    int arr[] = {9, 3, 4, 5, 7};
    int cnt = 0;
    int ret_val = SUCCESS;

    cnt = sizeof(arr)/ sizeof(arr[0]);

    bubble_sort(arr, cnt);
    print_arr(arr, cnt);

    return(ret_val);
}
