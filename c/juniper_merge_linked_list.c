/*
 * Sorted linked list
 * Input: Head *H1, *H2
 * Merge & maintain order
 * 
 */

typedef enum syserr_ {
    SUCCESS                 = 0,
    SYSERR_INVALID_PARAM    = 1,
    SYSERR_END_OF_LIST      = 2,
} syserr_t;

typedef struct node_ {
    uint32_t    val;
    struct node_ *next;
} node_t;

node_t *
get_next_node (node_t * node_p, syserr_t *status_p)
{
    if (node_p == NULL) {
        if (status_p != NULL) {
            *status_p = SYSERR_INVALID_PARAM;
        }
        printf("Invalid parameter\n");
        return(NULL);
    }

    if (node_p->next == NULL) {
        *status_p = SYSERR_END_OF_LIST;
        return(NULL);
    }

    *status_p = SUCCESS;
    return(node_p->next);
}

node_t *
merge_two_list (node_t *head_1_p, node_t *head_2_p, syserr_t *status_p)
{
    node_t *node_lst_1 = NULL;
    node_t *node_lst_2 = NULL;
    node_t *temp_node_p = NULL;
    syserr_t ret_val = SUCCESS;

    if ((head_1_p == NULL) || (head_2_p == NULL)) {
        if (status_p != NULL) {
            *status_p = SYSERR_INVALID_PARAM;
        }
        printf("Invalid parameter\n");
        return(NULL);
    }

    // Travere head_1_p & head_2_p
    // Pick node & compare val
    // Insert smaller val to head_1_p
    // If either list-1 or list-2 has reached end, merge pending from other list
    // Return

    node_lst_1 = head_1_p;
    node_lst_2 = head_2_p;

    while ((node_lst_1 != NULL) && (node_lst_2 != NULL)) {
        if (node_lst_1->val < node_lst_2->val) {
            temp_node_p = node_lst_2;
            node_lst_2 = get_next_node(node_lst_2, &ret_val);
            if ((node_lst_2 == NULL) && (ret_val == SYSERR_END_OF_LIST)) {
                // Handle end of list case
            } else if ((node_lst_2 != NULL) && (ret_val == SUCCESS)) {
                temp_node_p->next = node_lst_1->next;
                node_lst_1->next = temp_node_p;
            }
        }
    }

}
