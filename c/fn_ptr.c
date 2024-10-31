#include <stdio.h>

void
tst_fn (int num)
{
    printf("%s working, num = '%d'\n", __FUNCTION__, num);
    return;
}

typedef void
(*fn_ptr_t) (int );

int
main ( )
{
    fn_ptr_t fn_ptr;

    fn_ptr = tst_fn;
    fn_ptr(1);
    (*fn_ptr)(2);

    fn_ptr = &tst_fn;
    fn_ptr(3);
    (*fn_ptr)(4);

    return(0);
}
