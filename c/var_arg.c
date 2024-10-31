#include <stdio.h>
#include <stdarg.h>

#define SUCCESS     0

typedef struct _varg {
    int i:4;
    char str[10];
} varg_t;

int
(*var_arg_fn_p) (int , ...);

int
var_arg (int , ...);


int
main (void)
{
    int cnt = 2;
    int ret_val = SUCCESS;

    var_arg_fn_p = var_arg;
    var_arg_fn_p(cnt, 4, 9);
    cnt = 3;
    (*var_arg_fn_p)(cnt, 5, 4, 9);

    return(ret_val);
}

int
var_arg (int cnt, ...)
{
    int i = 0;
    int ret_val = SUCCESS;
    va_list valst;

    va_start(valst, cnt);

    for (i = 0; i < cnt; i++) {
        printf("Argument[%d] = '%d'\n", i, va_arg(valst, int));
    }

    va_end(valst);

    return(ret_val);
}
