#include <stdio.h>

#define SUCCESS             0
#define printf(msg, ...)    printf("\n"msg, ##__VA_ARGS__)

int
main (void)
{
    int i = 0;
    float f = 0;
    char c = 0;
    int ret_val = SUCCESS;

    printf("Enter integer prefixed with non-int: ");
    scanf("%*s %i", &i);
    getchar();
    printf("Here's the int part '%d'\n", i);

    printf("Enter float prefixed with non-number: ");
    scanf("%*s %f", &f);
    getchar();
    printf("Here's the float part '%f'\n", f);

    printf("Enter character prefixed with non-char: ");
    scanf("%*d %c", &c);
    getchar();
    printf("Here's the char part '%c'\n", c);

    return(ret_val);
}

/*
Enter integer prefixed with non-int: adfdf 4

Here's the int part '4'

Enter float prefixed with non-number: adf 5.4

Here's the float part '5.400000'

Enter character prefixed with non-char: 549c

Here's the char part 'c'
 */
