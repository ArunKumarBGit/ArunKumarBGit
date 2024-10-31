#include <stdio.h>

/*
 * Input: L1 -> L2 -> L3 -> ... L(n-2) -> L(n-1) -> Ln
 * Output: L1 -> Ln -> L2 -> L(n-1) -> L3 -> L(n-2) -> ...
 *
 * Input:  [1, 2, 3, 4, 5, 6]
 * Output: [1, 6, 2, 5, 3, 4]
 * 
 * Note: Values in the nodes shouldn't be modified
 *       Only nodes themselves needs to be shifted/ shuffled
 */

int main() {
    // you can write to stdout for debugging purposes, e.g.
    printf("This is a debug message\n");

    return 0;
}

struct node 
{
  int data;
  struct node *next;
};

int node_identifier = 0;
struct node *tail_node_p = NULL;

struct node *
get_next_tail_node(struct node * curr_node_p)
{
  if (curr_node_p != NULL) {
    get_next_tail_node(curr_node_p->next);
  }

  if (node_identifier == 1) {
    tail_node_p = curr_node_p->next;
    curr_node_p->next = NULL;
    node_identifier++;
  } else {
    node_identifier++;
  }

  return(tail_node_p);
}

struct node *
shuffle (struct node *head)
{
    struct node *curr_node_p = NULL;
    struct node *tail_node_p = NULL;
    struct node *temp_node_p = NULL;

    if (head == NULL) {
      printf("Invalid parameter passed\n");
      return(NULL);
    }

    curr_node_p = head;

    while (curr_node_p != NULL) {
      node_identifier = 0;
      tail_node_p = NULL;

      tail_node_p = get_next_tail_node(curr_node_p);

      if (curr_node_p == tail_node_p) {
        curr_node_p = NULL;
        continue;
      }

      // Insert inbetween
      temp_node_p = curr_node_p->next;
      curr_node_p->next = tail_node_p;
      tail_node_p->next = temp_node_p;

      // Move to next node
      curr_node_p = temp_node_p;
    }

    return(head);
}

