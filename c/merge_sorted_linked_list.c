/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

void
move (struct ListNode **dest, struct ListNode **src)
{
    (*dest)->next = *src;
    *src = (*src)->next;
    *dest = (*dest)->next;
}

struct ListNode* 
mergeTwoLists (struct ListNode* list1, struct ListNode* list2)
{
    struct ListNode temp_node;
    struct ListNode *head = &temp_node;
    struct ListNode *cur_node = head;
    
    if ((list1 == NULL) && (list2 != NULL)) {
        return(list2);
    } else if ((list1 != NULL) && (list2 == NULL)) {
        return(list1);
    } else if ((list1 == NULL) && (list2 == NULL)) {
        return(list1);
    }
    
    while (1) {
        if (list1 == NULL) {
            cur_node->next = list2;
            break;
        } else if (list2 == NULL) {
            cur_node->next = list1;
            break;
        }
        
        if (list1->val <= list2->val) {
            move(&cur_node, &list1);
        } else {
            move(&cur_node, &list2);
        }
    }
    
    return(head->next);
}
