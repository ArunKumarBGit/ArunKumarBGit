typedef void (*func_t)(void);

// already implemented
struct worker; 
void worker_init(struct worker * w, func_t work_f); // doesn't start work_f
void worker_start(struct worker * w, func_t callback_f); // create a new thread which will run work_f, then callback_f. start new thread. worker_start returns. new thread runs work_f, callback_f, then dies.


// define any globals here
#define MAX_SCALE_NUM   100
pthread_t th[MAX_SCALE_NUM];

typedef struct stack_ {
    int top;
    int max_frame;
    func_t *func;
};

typdef struct cleanup_hdl_ {
    int param_num_th;
    func_t callback_f;
} cleanup_hdl_t;

// Functions
void 
multiworker_init () 
{
    stack_init(MAX_SCALE_NUM);
}

void 
multiworker_add_work (func_t work_f) 
{
    push(work_f);
}

void *
cleanup_thread(void *param_p) {
    cleanup_hdl_t cleanup_hdl = *(cleanup_hdl_t *)param_p;
    int i = 0;
    
    for (i = 0; i < cleanup_hdl.param_num_th; i++) {
        pthread_join(th[i], NULL);
    }
    
    cleanup_hdl_p.callback_f();
    
    free(param_p);
}

// start all previously added work functions in background and call callback_f once when all work functions are complete.
// non-blocking
void 
multiworker_start (func_t callback_f) 
{
    int num_th = 0;
    cleanup_hdl_t *cleanup_hdl_p = NULL;
    
    while(!is_stack_empty()) {
        work_f = pop();
        
        pthread_create(&th[num_th++], NULL, work_f, NULL);
    }
    
    cleanup_hdl_p  = (int *)malloc(sizeof(cleanup_hdl_t));
    cleanup_hdl_p->param_num_th = num_th;
    cleanup_hdl_p->callback_f = callback_f;
    
    pthread_create(&th[num_th++], NULL, &cleanup_thread, cleanup_hdl_p);
    
    return;
}
