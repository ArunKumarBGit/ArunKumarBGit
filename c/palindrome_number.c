#include <stdio.h>

#define SUCCESS             0
#define printf(msg, ...)    printf("\n"msg"\n", ##__VA_ARGS__)

void
is_palindrome_number (unsigned int num) {
    int i = 0;
    unsigned int rev_num = 0;
    unsigned int num_cp = num;

    while (num_cp) {
        rev_num = rev_num * 10 + (num_cp % 10);
        num_cp /= 10;
    }

    printf("num = '%d', rev_num = '%d'", 
            num, rev_num);

    if (num == rev_num)
        printf("Palindrome number");
    else
        printf("Not Palindrome number");
}

int
main (void)
{
    int ret_val = SUCCESS;

    is_palindrome_number(459);
    is_palindrome_number(494);

    return(ret_val);
}
