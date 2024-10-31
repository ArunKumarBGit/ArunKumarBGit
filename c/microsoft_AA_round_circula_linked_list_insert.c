/*
 # Feedback:
 #  . Don't assume about the Linked list: 
 #    > Data may not be unique & have redundant values
 #    > Number of node(s) could be even '1', pointing itself
 #  . Don't use 'curr_node_p = curr_node_p->next;'
 #    > Write get_next_unique_node function
 #    > That function should check all possible validation
 #      * Single node check
 #      * In case of node with redundant 'val', skip & proceed to next
 #      * Return meaningful error codes
 */

/*
 * Requirement:
 *  . Circular Linked List
 *  . Sorted as/ ds
 *  . ptr to some node would be given
 *  . Insert new node and retain the same order
 */

// Approach:
//  . Identify the order :: as/ ds
//  . Insert to right place

typedef struct node_ {
    uint32_t val;
    struct node_ *next;
} node_t

typedef enum order_ {
    AS_ORDER    = 1,
    DS_ORDER    = 2
} order_t;

typedef enum syserr_ {
    SUCCESS         = 0,
    INVALID_PARAM   = 1
} syserr_t;

syserr_t
identify_order(node_t *node_p, order_t *order_p);

syserr_t
insert_node(node_t *cur_node_p, node_t *new_node_p);


syserr_t
identify_order (node_t *node_p, order_t *order_p) 
{
    node_t *curr_node_p = NULL;
    uint32_t val_1 = 0;
    uint32_t val_2 = 0;
    uint32_t val_3 = 0;

    if ((node_p == NULL) || (order_p == NULL)) {
        printf("Invalid parameter\n");
        return(INVALID_PARAM);
    }

    curr_node_p = node_p;
    val_1 = curr_node_p->val;

    curr_node_p = curr_node_p->next;
    val_2 = curr_node_p->val;

    curr_node_p = curr_node_p->next;
    val_3 = curr_node_p->val;
    
    if ((val_1 < val_2) && (val_2 < val_3)) {
        *order_p = AS_ORDER;
    }

    return(SUCCESS);
}
