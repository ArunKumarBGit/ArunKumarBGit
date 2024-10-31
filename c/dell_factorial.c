#include <stdio.h>
/*
 * Factorial
 * 5! = 5 X 4 X 3 X 2 X 1
 */

typedef enum syserr_ {
    SYSERR_SUCCESS          = 0,
    SYSERR_INVALID_PARAM    = 1,
    SYSERR_MAX              = 2
} syserr_t;
syserr_t
get_factorial (unsigned int num, unsigned int *fact_p)
{
    int i = 0;

    if (fact_p == NULL) {
        printf("Invalid parameter\n");
        return(SYSERR_INVALID_PARAM);
    }

    if (num == 0) {
        return(1);
    }

    *fact_p = 1;

    for (i = 1; i <= num; i++) {
        (*fact_p) *= i;
    }

    return(SYSERR_SUCCESS);
}

int
main (void)
{
    unsigned int    num = 5;
    unsigned int    fact = 0;
    syserr_t        ret_val = SYSERR_SUCCESS;

    ret_val = get_factorial(num, &fact);
    if (ret_val != SYSERR_SUCCESS) {
        printf("Failed to get factorial value for '%d', ret_val = '%d'\n", 
               num, ret_val);
        return(ret_val);
    }

    printf("Factorial of '%d' = '%d'\n\n", num, fact);

    return(ret_val);
}
