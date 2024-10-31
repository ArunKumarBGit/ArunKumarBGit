#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
4
3
4
2
7

Ans = 3;
4 - appeared twice; Others appeared once only;
 */

/*
 * Complete the 'odd_occurring_num' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

int odd_occurring_num(int arr_count, int* arr) {
    int count[32] = {[0 ... 31] = 0};
    int total_odd_num = 0;
    int i = 0;
    
    for (i = 0; i < arr_count; i++) {
        if (arr[i] <= 31) {
            count[arr[i]]++;
        } else {
            printf("Invalid data %d\n", arr[i]);
            return(-1);
        }
    }
    
    for (i = 0; i < 32; i ++) {
        if (count[i] & 0x1) {
            total_odd_num++;
        }
    }
    return(total_odd_num);
}

int
main (void)
{
    int arr[5] = {4, 3, 4, 2, 7};

    printf("\nBirthdays = %d %d %d %d %d\n",
           arr[0], arr[1], arr[2], arr[3], arr[4]);
    printf("\nOdd occurring numbers = '%d'\n\n",
            odd_occurring_num(5, arr));

    return(0);
}
