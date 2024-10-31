#include <stdio.h>
#include <stdlib.h>

#define SUCCESS             0
//#define printf(msg, ...)    printf("\n"msg"\n", ##__VA_ARGS__)

typedef struct bst_node_ {
    int data;
    struct bst_node_ *left_p;
    struct bst_node_ *right_p;
}bst_node_t;

bst_node_t *
add_new_node(int data) 
{
    bst_node_t *node_p = NULL;

    node_p = (bst_node_t *)malloc(sizeof(bst_node_t));
    if (node_p == NULL) {
        return node_p;
    }

    node_p->data = data;
    node_p->left_p = NULL;
    node_p->right_p = NULL;

    return node_p;
}

bst_node_t *
add_array_to_bst (int arr[], int start, int end)
{
    int mid = 0;
    bst_node_t *roo_p = NULL;

    if (start > end) {
        return (NULL);
    }

    mid = (start + end)/2;

    bst_node_t *root_p = add_new_node(arr[mid]);
    if (root_p == NULL) {
        printf("Failed to add new node");
        return (NULL);
    }

    root_p->left_p = add_array_to_bst(arr, start, mid-1);
    root_p->right_p = add_array_to_bst(arr, mid+1, end);

    return(root_p);
}

void
disp_bst_preorder (bst_node_t *root_p)
{
    if (root_p == NULL) {
        return;
    }

    printf("%d ", root_p->data);

    disp_bst_preorder(root_p->left_p);
    disp_bst_preorder(root_p->right_p);
}

void
disp_bst_inorder (bst_node_t *root_p)
{
    if (root_p == NULL) {
        return;
    }

    disp_bst_inorder(root_p->left_p);
    printf("%d ", root_p->data);
    disp_bst_inorder(root_p->right_p);

    return;
}

void
disp_bst_postorder (bst_node_t *root_p)
{
    if (root_p == NULL) {
        return;
    }

    disp_bst_postorder(root_p->left_p);
    disp_bst_postorder(root_p->right_p);
    printf("%d ", root_p->data);

    return;
}

int
main (void)
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int cnt = 0;
    bst_node_t *root_p = NULL;
    int ret_val = SUCCESS;

    cnt = sizeof(arr)/ sizeof(arr[0]);

    root_p = add_array_to_bst(arr, 0, cnt-1);

    disp_bst_preorder(root_p);
    printf("\n");
    disp_bst_inorder(root_p);
    printf("\n");
    disp_bst_postorder(root_p);
    printf("\n");

    return(ret_val);
}
