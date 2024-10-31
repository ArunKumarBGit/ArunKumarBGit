// 5 guests - round table - noodles at center
// 5 chopsticks between two guests
// Get two copsticks to eat (or) talk otherwise

// Circular double linked list with 5 nodes

// Sudo code
 . Each thread to handle one node/ guest
 . Check left node right_ct is available (0) and :: (node_p->left->right_ct == 0)
   Check if right node left_ct is available         (node_p->right->left_ct == 0)
 . If so, grab both the chopsticks & eat
 . Use mutex lock for thread sync
 . Else retry
 . After eating, release the chopsticks

wait( );
signal( );

typedef struct semaphore_ {
    unsigned int max_resource;
    unsigned int cnt
} semaphore_t;

semaphore_t sema_gbl[5];

typedef struct node_ {
    struct node_ *left;
    unsigned int node_id;
    unsigned int lock_id_left;  // 4
    unsigned int lock_id_right; // 0
    struct node_ *right;
} node_t;

int
wait (semaphore_t *sema_p) {

    if (sema_p == NULL) {
        return(INVALID_PARAM);
    }

    while (1) {
        if (sema->cnt > 0) {
            sema->cnt--;
            return(SUCCESS);
        } else {
            schedule(500); // 500 ms
        }
    }

    return(0);
}

int
signal (semaphore_t *sema_p) {
    if (sema_p == NULL) {
        return(INVALID_PARAM);
    }

    if (sema_p->cnt < sema_p->max_resource) {
        sema_p->cnt++;
        return(SUCCESS);
    } else {
        return(INVALID_CNT);
    }

    return(0);
}

#define NUM_GUESTS  5
#define SUCCESS     0

int
guest_thread_internal (node_t *node_p)
{
    // Ensure no dead lock in next phase
    int ret_val = 0;

    if (node_p == NULL) {
        ERROR_LOG("NULL parameter");
        return(INVALID_PARAM);
    }

    // Acquire left side chopstick
    ret_val = wait(sema_gbl[node_p->lock_id_left]);
    if (ret_val != SUCCESS) {
        ERROR_LOG("Failed during semaphore wait left, ret_val = '%d'\n", ret_val);
        return(ret_val);
    }

    // Acquire right side chopstick
    ret_val = wait(sema_gbl[node_p->lock_id_right]);
    if (ret_val != SUCCESS) {
        ERROR_LOG("Failed during semaphore wait right, ret_val = '%d'\n", ret_val);
        return(ret_val);
    }

    // Got both chopsticks
    printf("Guest '%d' eating noodles\n", node_p->node_id);

    // Release right side chopstick
    ret_val = signal(sema_gbl[node_p->lock_id_right]);
    if (ret_val != SUCCESS) {
        ERROR_LOG("Failed during semaphore signal right, ret_val = '%d'\n", ret_val);
    }

    // Release left side chopstick
    ret_val = signal(sema_gbl[node_p->lock_id_left]);
    if (ret_val != SUCCESS) {
        ERROR_LOG("Failed during semaphore signal left, ret_val = '%d'\n", ret_val);
    }

    return(ret_val);
}

int
guest_thread (node_t *node_p) {
    int ret_val = 0;

    while(1) {
        ret_val = guest_thread_internal(node_p);
        // Exit condition to be defined
    }

    return(0);
}

int
main (void)
{
    pthread_handle_t thread_hdl[NUM_GUESTS];
    node_t node[NUM_GUESTS];
    int i = 0;
    int ret_val = 0;

    // Create doubly linked list for node[NUM_GUESTS]
    // Initialize doubly linked list with lock_id_left & lock_id_right

    for (i = 0; i < NUM_GUESTS; i++) {
        ret_val = pthread_create(&thread_hdl[i], guest_thread, 
                                 &node[i], NULL);
        if (ret_val != SUCCESS) {
            ERROR_LOG("Failed to create thread '%d', ret_val = '%d'\n",
                       i+1, ret_val);
            return(ret_val);
        }
    }

    for (i = 0; i < NUM_GUESTS; i++) {
        ret_val = pthread_join(&thread_hdl[i]);
        if (ret_val != SUCCESS) {
            ERROR_LOG("Failed to join thread '%d', ret_val = '%d'\n",
                       i+1, ret_val);
        }
    }

    return(0);
}
