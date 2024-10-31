
typedef enum tlv_type_ {
    TLV_TYPE_INVALID    = 0,
    TLV_TYPE_INT        = 1,
    TLV_TYPE_STR        = 2,
    TLV_TYPE_CHAR       = 3,
    
    TLV_TYPE_MAX        = 4

} tlv_type_t;

typedef struct tlv_data_ {
    tlv_type_t type;
    int length;
    int val[0];
} tlv_data_t;

typedef struct node_ {
    tlv_data_t data;
    node_t *next;
} node_t;

typedef struct itr_hdl_t {
    node_t *head_p;
    node_t *curr_p;
    tlv_type_t type;
} itr_hdl_t;


itr_hdl_t *
init_handler (node_t *head_p, tlv_type_t type)
{
    itr_hdl_t hdl_p = NULL
    
    if ((head_p == NULL) || ((type <= TLV_TYPE_INVALID) && (type >= TLV_TYPE_MAX))) {
        return(NULL);
    }
    
    hdl_p = (itr_hdl_t *)malloc(sizeof(itr_hdl_t));
    if (hdl_p == NULL) {
        return(NULL);
    }
    
    hdl_p->head_p = head_p;
    hdl_p->curr_p = head_p;
    hdl_p->type = type;
    
    return(hdl_p);
}


node_t *
get_next (itl_hdl_t *hdl_p)
{
    if ((hdl_p == NULL) || (hdl_p->curr_p == NULL)) {
        return(NULL);
    }
    
    hdl_p->curr_p = hdl_p->curr_p->next;
    
    return(hdl_p->curr_p);
}



node_t *
has_next (itl_hdl_t *hdl_p)
{
    node_t *cur_node_p = NULL
    if (hdl_p == NULL) {
        return(NULL);
    }
    
    while (hdl_p->curr_p != NULL) {
        cur_node_p = get_next(hdl_p);
        
        if (cur_node_p == NULL) {
            return(NULL);
        } else if (curr_node_p->type == hdl_p->type) {
            return(curr_node_p);
        }
    }
    
    return(NULL);
}

/*
    CHAR, INT, INT, STR, CHAR, CHAR, INT, STR       :: STR

*/


#if 0 
typedef struct type_ {
	int type;
	int datalen;
} DATA_TYPE;

typedef struct data_ {
	int type;
	int datalen;
	// variable size data
	void data[0]; // Arun B :: Place holder for data
} USER_DATA;

DATA_TYPE user_data_type[] = {{1, 23}, {2, 40}, {3, 32}};
USER_DATA *g_user_data = NULL;

USER_DATA *alloc(DATA_TYPE *type, int num)
{
	int i, size = 0;
	USER_DATA *g_data, *ptr;

	for (i = 0; i < num; i++) {
		size += sizeof (USER_DATA) + type[i].datalen;
    }
    g_data = (USER_DATA *)malloc(size);
    
    if (!g_data)
        return (NULL);
        
	ptr = g_data;
	for (i = 0; i < num; i++) {
		ptr->type = type[i].type;
		ptr->datalen = type[i].datalen;
		memset(ptr->data, 0, type[i].datalen);
		ptr = ((char *)ptr) + sizeof (USER_DATA) + type[i].datalen;
	}
	return (g_data);
}

int main()
{
	g_user_data = alloc(user_data_type, 3);
}

#endif
