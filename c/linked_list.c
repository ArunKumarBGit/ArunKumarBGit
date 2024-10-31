#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef struct node_ {
    unsigned int num;
    struct node_ *next;
} node_t;

typedef enum syserr_ {
    SYSERR_SUCCESS      = 0,
    SYSERR_NULL_PTR     = 1,
    SYSERR_INVALID_ARG  = 2,
    SYSERR_ALLOC_FAILED = 3,
    SYSERR_FREE_FAILD   = 4,
    SYSERR_UNDERFLOW    = 5,
    SYSERR_OVERFLOW     = 6,

    /* Add new entries above this line */
    SYSERR_MAX          = SYSERR_OVERFLOW + 1,
} syserr_t;

#define log_err printf   // Revisit here

syserr_t
create_new_node (node_t **node_pp, unsigned int num)
{
    if (node_pp == NULL) {
        log_err("Invalid parameter, node_pp is NULL\n");
        return(SYSERR_NULL_PTR);
    }

    *node_pp = (node_t *) malloc(sizeof(node_t));
    if (*node_pp == NULL) {
        log_err("Memory allocation failed for new node\n");
        return(SYSERR_ALLOC_FAILED);
    }

    // Initialize the new node
    (*node_pp)->num = num;
    (*node_pp)->next = NULL;

    return(SYSERR_SUCCESS);
}


syserr_t
push_node (node_t **tos_pp, unsigned int num)
{
    node_t *new_node_p = NULL;
    syserr_t ret_val = SYSERR_SUCCESS;

    if (tos_pp == NULL) {
        log_err("Invalid parameter, tos_pp = 0x%lx\n", (long)tos_pp);
        return(SYSERR_NULL_PTR);
    }

    ret_val = create_new_node(&new_node_p, num);
    if (ret_val != SYSERR_SUCCESS) {
        log_err("Failed to create new node\n");
        return(ret_val);
    }

    // Form the stack chain
    new_node_p->next = *tos_pp;

    // Update the top of stack
    *tos_pp = new_node_p;

    return(SYSERR_SUCCESS);
}


syserr_t
pop_node (node_t **tos_pp, unsigned int *num_p)
{
    node_t *free_node_p = NULL;

    if ((tos_pp == NULL) || (num_p == NULL)) {
        log_err("Invalid parameter, tos_pp = 0x%lx, num_p = 0x%lx\n",
                (long)tos_pp, (long)num_p);
        return(SYSERR_NULL_PTR);
    }

    free_node_p = *tos_pp;

    if (free_node_p == NULL) {
        log_err("\nStack is already empty\n");
        return(SYSERR_UNDERFLOW);
    }

    // Fetch the value
    *num_p = free_node_p->num;

    // Update the top of stack
    (*tos_pp) = free_node_p->next;

    // Free the node
    free(free_node_p);

    return(SYSERR_SUCCESS);
}

syserr_t
create_stack (node_t **tos_pp, unsigned int num)
{
    return(create_new_node(tos_pp, num));
}

syserr_t
destroy_stack (node_t **tos_pp)
{
    unsigned int num = 0;

    while (pop_node(tos_pp, &num) != SYSERR_UNDERFLOW) {
        printf("\n\nPoped node num = '%d'\n", num);
    }

    return(SYSERR_SUCCESS);
}


int 
main ()
{
    node_t  *tos_p = NULL;
    node_t  *node_p = NULL;
    unsigned int num = 0;
    syserr_t ret_val = SYSERR_SUCCESS;

    ret_val = create_stack(&tos_p, 194);
    if (ret_val != SYSERR_SUCCESS) {
        log_err("Failed to create stack\n");
        return(ret_val);
    }

    ret_val = push_node(&tos_p, 90);
    if (ret_val != SYSERR_SUCCESS) {
        log_err("Failed to push a node\n");
        return(ret_val);
    }

    ret_val = push_node(&tos_p, 40);
    if (ret_val != SYSERR_SUCCESS) {
        log_err("Failed to push a node\n");
        return(ret_val);
    }

    ret_val = push_node(&tos_p, 54);
    if (ret_val != SYSERR_SUCCESS) {
        log_err("Failed to push a node\n");
        return(ret_val);
    }

    ret_val = pop_node(&tos_p, &num);
    if (ret_val != SYSERR_SUCCESS) {
        log_err("Failed to pop a node\n");
        return(ret_val);
    }

    printf("\n\nnum = %d\\n", num);

    ret_val = destroy_stack(&tos_p);
    if (ret_val != SYSERR_SUCCESS) {
        log_err("Failed to destroy the stack\n");
        return(ret_val);
    }

    return (0);
}
