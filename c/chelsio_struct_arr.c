#include <stdio.h>
#include <stdlib.h>

struct node_ {
    int val;
    struct node_ *next;
};

int
main (void)
{
    struct node_ *lst = NULL;

    lst = (struct node_ *)malloc(5 * sizeof(struct node_));

    lst[4].val = 900;

    printf("\nsizeof node = '%lu', lst[4].val = '%d', (lst + 4)->val = '%d'\n\n", 
           sizeof(struct node_), lst[4].val, (lst+4)->val);

    return(0);
}
