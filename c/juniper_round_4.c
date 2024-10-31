volatile int id = 0;

int get_id()
{
    int temp_id = 0;
  get_lock();
  id++;
  temp_id = id;
  release_loack();
  
  return(temp_id);
}


volatile int id = 0;

node *
get_second_largest(node *root_p)
{
    node *sec_lar_node_p = NULL;
    if (root_p->right != NULL) {
        sec_lar_node_p = get_second_largest(root_p->right);
    } else if ((root_p->right == NULL) && (root_p->left != NULL)) {
        sec_lar_node_p = get_second_largest(root_p->left);
    } else if ((root_p->right == NULL) && (root_p->left == NULL)) {
        return(root_p);
    }

    return(sec_lar_node_p);
}

node * second_largest(node * root)
{
    if (root == NULL) {
        printf("Invalid parameter\n");
        return(NULL);
    }

    return(get_second_largest(root));
}
