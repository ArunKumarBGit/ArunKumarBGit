/*
 * Producer → Queue → Consumer
 * Queue - finite & need to be like circular in nature
 * Critical section handling
 * Signaling between Producer & Consumer, about queue entry addition/ removal
 *   . Handles Empty/ Full queue cases
 *
 */

Critical section handling → Mutex
Signaling → Semaphore
Circular queue → Modulo

#define BUFFER_SIZE_MAX        1024

semaphore empty = BUFFER_SIZE_MAX;
semaphore full = 0;

producer {
 wait(empty);
 lock(queue_mutex);

 enqueue(buffer);

 unlock(queue_mutex);
 signal(full);
}

consumer {
 wait(full);
 lock(queue_mutex);

 dequeue(buffer);

 unlock(queue_mutex);
 signal(empty);
}

int circular_buffer[BUFFER_SIZE_MAX];
int prod_idx = -1;
int cons_idx = 0;

typedef enum syserr_ {
     SYSERR_SUCCESS = 0,
    SYSERR_INVALID_PARAM = 1
} syserr_t;



syserr_t
enqueue (int data)
{
    prod_idx++;
    prod_idx %= BUFFER_SIZE_MAX;

    circular_buffer[prod_idx] =data;

    return(SYSERR_SUCCESS);
}


syserr_t
dequeue (int *data_p)
{
    if (data_p == NULL) {
        printf(“Invalid parameter\n”);
        return(SYSERR_INVALID_PARAM);
    }

    *data_p = circular_buffer[cons_idx];

    cons_idx++;
    cons_idx %= BUFFER_SIZE_MAX;


    return(SYSERR_SUCCESS);
}

syserr_t
is_queue_full(queue_handle_t *hdl_p, bool *is_full_p)
{
    if ((hdl_p == NULL) || (is_full_p  == NULL)) {
        printf(“Invalid parameter\n”);
        return(SYSERR_INVALID_PARAM);
    }

    if (hdl_p.cnt == BUFFER_SIZE_MAX) {
        *is_full_p = TRUE;
     } else {
        *is_full_p = FALSE;
    }

    return(SYSERR_SUCCESS);
}

