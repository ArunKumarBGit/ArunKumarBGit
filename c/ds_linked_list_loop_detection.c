/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

// Floyd’s Cycle-Finding Algorithm

bool 
hasCycle (struct ListNode *head)
{
    struct ListNode *slow_ptr = head;
    struct ListNode *fast_ptr = head;
    
    if (head == NULL) {
        return(0);
    }
    
    if (head->next == NULL) {
        return(0);
    }
    
    while (slow_ptr && fast_ptr && fast_ptr->next) {
        slow_ptr = slow_ptr->next;
        fast_ptr = fast_ptr->next->next;
        
        if (slow_ptr == fast_ptr) {
            return(1);
        }
    }
    
    return(0);
}
