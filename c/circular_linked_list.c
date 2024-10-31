#include <stdio.h>
#include <stdlib.h>

typedef struct list_node_ {
    int val;
    struct list_node_ *next_p;
} list_node_t;

typedef enum syserr_ {
    SYSERR_SUCCESS          = 0,
    SYSERR_INVALID_PARAM    = 1,
    SYSERR_ALLOC_FAILED     = 2,
} syserr_t;

syserr_t
add_node (list_node_t **cur_node_pp, int val)
{
    list_node_t *new_node_p = NULL;

    if (cur_node_pp == NULL) {
        printf("Invalid parameter\n");
        return(SYSERR_INVALID_PARAM);
    }

    new_node_p = (list_node_t *) malloc(sizeof(list_node_t));
    if (new_node_p == NULL) {
        printf("Failed to allocate memoery for new_node_p\n");
        return(SYSERR_ALLOC_FAILED);
    }

    new_node_p->val = val;

    if (*cur_node_pp == NULL) {
        *cur_node_pp = (list_node_t *) malloc(sizeof(list_node_t));
        if (*cur_node_pp == NULL) {
            printf("Failed to allocate memoery for *cur_node_pp\n");
            return(SYSERR_ALLOC_FAILED);
        }
        
        *cur_node_pp = new_node_p;
        (*cur_node_pp)->next_p = *cur_node_pp; // circular
    } else {
        new_node_p->next_p = (*cur_node_pp)->next_p;
        (*cur_node_pp)->next_p = new_node_p;
    }

    return(SYSERR_SUCCESS);
}

void
print_list (list_node_t *node_p)
{
    list_node_t *start_node_p = node_p;
    if (node_p == NULL) {
        printf("Empty circular list\n");
        return;
    }

    while (1) {
        printf("%d -> ", node_p->val);

        if (node_p->next_p == start_node_p) {
            printf("\n"); // Completed one full round
            break;
        } else {
            node_p = node_p->next_p;
        }
    }
}

int
main (void)
{
    list_node_t *head_p = NULL;
    syserr_t    ret_val = SYSERR_SUCCESS;

    ret_val = add_node(&head_p, 4);
    if (ret_val != SYSERR_SUCCESS) {
        printf("add_node failed, ret_val = '%d'\n", ret_val);
        return(ret_val);
    }

    print_list(head_p);

}
