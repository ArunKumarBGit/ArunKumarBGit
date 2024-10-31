/*
 * Producer - Consumer
 * Circular FIFO - 1 to 10
 * Producer idx, Consumer idx
 * Write funtion to check queue_full & queue_empty
 */

#define MAX_QUEUE_SIZE      10

typedef enum syserr_ {
    SYSERR_SUCCESS          = 0,
    SYSERR_INVALID_PARAM
} syserr_t;

syserr_t
is_queue_full(queue_handle_t *hdl_p, bool *is_full_p)
{
    if ((hdl_p == NULL) || (is_full_p == NULL)) {
        printf("Invalid parameter\n");
        return(SYSERR_INVALID_PARAM);
    }

    if (hdl_p->cnt == MAX_QUEUE_SIZE) {
        *is_full_p = TRUE;
    } else {
        *is_full_p = FALSE;
    }

    return(SYSERR_SUCCESS);
}


0 1 ... 9

p_idx = 0;  9; 0 1
c_idx = 0;  0 1 2 ...         9;

Before wrap-around:
 . p_idx >= c_idx

if ((p_idx > c_idx) && ((p_idx - c_idx) == MAX_QUEUE_SIZE)) {
    FULL;
} else if (p_idx == c_idx) {
    FULL;
} else if ((p_idx < c_idx) && ((c_idx - p_idx) == MAX_QUEUE_SIZE)) {
    FULL;
}


How to check if it is balanced (corresponding opening/closing bracket/parentheses)

{[({})[()]]}

typedef enum brace_type_ {
    BRACE_TYPE_INVALID  = 0,
    BRACE_TYPE_PARAN    = 1,
    BRACE_TYPE_SQUARE   = 2,
    BRACE_TYPE_CURLEY   = 3,
    BRACE_TYPE_MAX      = 4
} brace_type_t;

typedef enum oper_type_ {
    OPER_TYPE_INVALID  = 0,
    OPER_TYPE_PUSH     = 1,
    OPER_TYPE_POP      = 2,
    OPER_TYPE_MAX      = 3
} oper_type_t;

syserr_t
is_balanced(char *str_p, unsigned int len, bool *is_balanced_p)
{
    unsigned int i      = 0;
    brace_type_t type   = BRACE_TYPE_INVALID;
    brace_type_t peek_type = BRACE_TYPE_INVALID;
    oper_type_t oper    = OPER_TYPE_INVALID;

    if ((str_p == NULL) || (len == 0) || (is_balanced_p == NULL)) {
        printf("Invalid parameter\n");
        return(SYSERR_INVALID_PARAM);
    }

    for (i = 0; i < len; i++) {
        switch(str_p[i]) {
            case '(':
                type = BRACE_TYPE_PARAN;
                oper = OPER_TYPE_PUSH;
                break;

            case ')':
                type = BRACE_TYPE_PARAN;
                oper = OPER_TYPE_POP;
                break;

            case '[':
                type = BRACE_TYPE_SQUARE;
                oper = OPER_TYPE_PUSH;
                break;

            case ']':
                type = BRACE_TYPE_SQUARE;
                oper = OPER_TYPE_POP;
                break;

            case '{':
                type = BRACE_TYPE_CURLEY;
                oper = OPER_TYPE_PUSH;
                break;

            case '}':
                type = BRACE_TYPE_CURLEY;
                oper = OPER_TYPE_POP;
                break;

            default:
                printf("Invalid character '%c' found\n", str_p[i]);
                return(SYSERR_INVALID_CHAR);
        }

        if (oper == OPER_TYPE_PUSH) {
            push(type);
        } else if (oper == OPER_TYPE_POP) {
            peek_type = peek();
            if (peek_type != type) {
                *is_balanced_p = FALSE;
                return(SYSERR_SUCCESS);
            } else {
                pop();
            }
        }
    }

    if (!is_stack_empty()) {
        *is_balanced_p = FALSE;
        return(SYSERR_SUCCESS);
    }

    *is_balanced_p = TRUE;
    return(SYSERR_SUCCESS);
}

