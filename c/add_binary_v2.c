#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *
addBinary (char * a, char * b)
{
    char val_a = 0;
    char val_b = 0;
    char carry = 0;
    char aj_used = 0;
    char bj_used = 0;
    long int i = 0;
    long int j = 0;
    char sum = 0;
    unsigned int len_a = 0;
    unsigned int len_b = 0;
    unsigned int len = 0;
    char *arr = NULL;

    len_a = strlen(a);
    len_b = strlen(b);
    len = (len_a > len_b) ? len_a : len_b;
    j = (len_a < len_b) ? len_a : len_b;

    arr = (char *)malloc(len + 1);
    arr[len] = '\0';

    for (i = len - 1; i >= 0; i--) {
        if ((i < len_a) && (aj_used == 0)) {
            val_a = a[i] - '0';
        } else if (j > 0) {
            val_a = a[--j] - '0';
            aj_used = 1;
        } else {
            val_a = 0;
        }

        if ((i < len_b) && (bj_used == 0)) {
            val_b = b[i] - '0';
        } else if (j > 0) {
            val_b = b[--j] - '0';
            bj_used = 1;
        } else {
            val_b = 0;
        }

        sum = val_a + val_b + carry;
        printf("\nval_a = '%d', val_b = '%d', carry = '%d', sum = '%d'\n\n",
                val_a, val_b, carry, sum);
        switch (sum) {
            case 0:
                arr[i] = '0';
                carry = 0;
                break;

            case 1:
                arr[i] = '1';
                carry = 0;
                break;

            case 2:
                arr[i] = '0';
                carry = 1;
                break;

            case 3:
                arr[i] = '1';
                carry = 1;
                break;
        }
    }

    if (carry) {
        char *ans = (char *)malloc(len+2);
        memcpy(ans+1, arr, len+1);
        ans[0] = '1';
        free(arr);
        arr = ans;
    }

    return(arr);
}

int
main (void)
{
    char a[] = "11";
    char b[] = "1";

    printf("\nsum of %s + %s = %s\n\n", a, b, addBinary(a, b));

    return (0);
}
