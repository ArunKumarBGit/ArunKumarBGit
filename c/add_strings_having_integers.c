#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char * 
addStrings (char * num1, char * num2) 
{
    int len_a = 0;
    int len_b = 0;
    int len = 0;
    int i = 0;
    int j = 0;
    int aj_used = 0;
    int bj_used = 0;
    int val_a = 0;
    int val_b = 0;
    int carry = 0;
    int tot = 0;
    char *sum = NULL;
    
    if ((num1 == NULL) || (num2 == NULL)) {
        printf("Invalid argument");
        return(NULL);
    }
    
    len_a = strlen(num1);
    len_b = strlen(num2);
    len = (len_a > len_b) ? len_a : len_b;
    j = (len_a < len_b) ? len_a : len_b;
    
    sum = (char *)malloc(len + 1);
    sum[len] = '\0';
    
    for (i = len - 1; i >= 0; i--) {
        // Value of num1
        if ((i < len_a) && (aj_used == 0)) {
            val_a = num1[i] - '0';
        } else if (j > 0) {
            val_a = num1[--j]  - '0';
            aj_used = 1;
        } else {
            val_a = 0;
        }
        
        // Value of num2
        if ((i < len_b) && (bj_used == 0)) {
            val_b = num2[i] - '0';
        } else if (j > 0) {
            val_b = num2[--j] - '0';
            bj_used = 1;
        } else {
            val_b = 0;
        }
        
        // Sum
        tot = val_a + val_b + carry;
        
        if (tot > 9) {
            sum[i] = '0' + tot % 10;
            carry = tot / 10;
        } else {
            sum[i] = '0' + tot;
            carry = 0;
        }
    }
    
    if (carry) {
        char *sum_nw = NULL;
        
        sum_nw = (char *)malloc(len + 2);
        //sum_nw[len + 1] = '\0';
        
        memcpy(sum_nw + 1, sum, (len + 1));
        sum_nw[0] = '0' + carry;
        
        free(sum);
        sum = sum_nw;
    }
    
    return(sum);
}


int
main (void)
{
    char num1[] = "11";
    char *num2 = "123";
    char *sum = NULL;
    int i = 0;

    sum = addStrings(num1, num2); 
    
    printf("\nnum1 = '%s', num2 = '%s', sum = '%s'\n\n",
           num1, num2, sum);

    return(0);
}
