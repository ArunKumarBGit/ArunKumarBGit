#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node_ {
    int val;
    struct node_ *next;
};

int
main (void)
{
    struct node_ *lst_p = NULL;

    lst_p = (struct node_ *)malloc(10 * sizeof(struct node_));
    memset(lst_p, 0, (10 * sizeof(struct node_)));

    (lst_p + 4)->val = 99;

    printf("\nValue of 5th node = '%d'\n\n", lst_p[4].val);

    return(0);
}
