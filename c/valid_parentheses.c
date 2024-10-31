#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE    1
#define FALSE   0
typedef char bool;

typedef enum _sym_type {
    SYM_TYPE_NONE       = 0,
    SYM_TYPE_BRACKET    = 1,
    SYM_TYPE_SQUARE     = 2,
    SYM_TYPE_BRACE      = 3,
    SYM_TYPE_MAX        = 4
} sym_type_t;

char *stack_p = NULL;
long long int sp = -1;
long unsigned int sz = 0;

void
push (sym_type_t sym_type)
{
    if (stack_p == NULL) {
        sz = 1;
        stack_p = (char *)malloc(sizeof(char));
        sp = 0;
    } else if ((sz - sp) > 1) {
        sp++;
    } else {
        sz++;
        stack_p = (char *)realloc(stack_p, (sz) * sizeof(char));
        sp++;
    }
    
    *(stack_p + sp) = sym_type;
    printf("sp = '%lld', sz = '%lu', sym_type = '%d'\n",
           sp, sz, sym_type);
}

bool
pop (sym_type_t sym_type)
{
    if ((stack_p == NULL) || (sp < 0)) {
        return(FALSE);
    }
    
    printf("sp = '%lld', sz = '%lu', stack_type = '%d', sym_type = '%d'\n",
           sp, sz, *(stack_p + sp), sym_type);
    if (*(stack_p + sp) == sym_type) {
        *(stack_p + sp) = SYM_TYPE_NONE;
        sp--;
        return(TRUE);
    } else {
        return(FALSE);
    }
}

void
cleanup_stack (void)
{
    if (stack_p != NULL) {
        free(stack_p);
        stack_p = NULL;
    }
}

bool
is_stack_empty (void)
{
    if ((stack_p == NULL) || (sp < 0)) {
        return(TRUE);
    } else {
        return(FALSE);
    }
}

bool 
isValid (char * s)
{
    long unsigned int len = 0;
    long unsigned int i = 0;
    bool ret_val = TRUE;
    
    if (s == NULL) {
        return(FALSE);
    }
    
    len = strlen(s);
    
    for (i = 0; i < len; i++) {
        switch (s[i]) {
            case '(':
                push(SYM_TYPE_BRACKET);
                break;

            case '[':
                push(SYM_TYPE_SQUARE);
                break;
                
            case '{':
                push(SYM_TYPE_BRACE);
                break;
                
            case ')':
                ret_val = pop(SYM_TYPE_BRACKET);
                if (ret_val == FALSE) {
                    cleanup_stack();
                    return(ret_val);
                }
                break;
                
            case ']':
                ret_val = pop(SYM_TYPE_SQUARE);
                if (ret_val == FALSE) {
                    cleanup_stack();
                    return(ret_val);
                }
                break;
                
            case '}':
                ret_val = pop(SYM_TYPE_BRACE);
                if (ret_val == FALSE) {
                    cleanup_stack();
                    return(ret_val);
                }
                break;
            
            default:
                cleanup_stack();
                return(FALSE);
        }
    }
    
    printf("i = '%lu', len = '%lu', is_stack_empty = '%d'\n",
           i, len, is_stack_empty());
    if ((i == len) && is_stack_empty()) {
        cleanup_stack();
        return(TRUE);
    } else {
        cleanup_stack();
        return(FALSE);
    }
}

int
main (void)
{
    char str[] = "(){}][";

    printf("\nstr = '%s', isValid = '%d'\n\n", str, isValid(str));

    return(0);
}
