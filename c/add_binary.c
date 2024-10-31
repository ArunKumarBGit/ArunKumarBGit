#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *
addBinary (char * a, char * b)
{
    int len_a = 0;
    int len_b = 0;
    int len = 0;
    int i = 0;
    int j = 0;
    char val_a = 0;
    char val_b = 0;
    char *sum = NULL;
    char carry = 0;
    char aj_used = 0;
    char bj_used = 0;

    if ((a == NULL) || (b == NULL)) {
        printf("Invalid parameter\n");
        return (NULL);
    }

    len_a = strlen(a);
    len_b = strlen(b);

    len = (len_a > len_b)? len_a : len_b;
    j = (len_a < len_b)? len_a : len_b;

    sum = (char *)malloc(len + 1);
    sum[len] = '\0';

    for (i = len-1 ; i >= 0; i--) {
        if ((i < len_a) && (aj_used == 0)) {
            val_a = (a[i] == '1') ? 1 : 0;
        } else if (j > 0) {
            val_a = (a[--j] == '1') ? 1 : 0;
            aj_used = 1;
        } else {
            val_a = 0;
        }

        if ((i < len_b) && (bj_used == 0)) {
            val_b = (b[i] == '1') ? 1 : 0;
        } else if (j > 0) {
            val_b = (b[--j] == '1') ? 1 : 0;
            bj_used = 1;
        } else {
            val_b = 0;
        }

        switch (val_a + val_b + carry) {
            case 0:
                sum[i] = '0';
                carry = 0;
                break;

            case 1:
                sum[i] = '1';
                carry = 0;
                break;

            case 2:
                sum[i] = '0';
                carry = 1;
                break;

            case 3:
                sum[i] = '1';
                carry = 1;
                break;
        }
    }

    if (carry == 1) {
        char *new_sum = NULL;
        new_sum = (char *)malloc(len+2);
        memcpy(new_sum + 1, sum, len+1);
        new_sum[0] = '1';
        free(sum);
        sum = new_sum;
        carry = 0;
    }

    return(sum);
}

int
main (void)
{
    char a[] = "11";
    char b[] = "1111";

    printf("\na = '%s', b = '%s', sum = '%s'\n\n", a, b, addBinary(a, b));

    return(0);
}
