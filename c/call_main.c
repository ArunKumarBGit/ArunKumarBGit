#include <stdio.h>

int main(void);

void
my_func (int num)
{
    if (num == 4) {
        main();
    }

    return;
}

int
main (void) {
    static int flag = 4;
    int num = flag--;

    if (num == 4) {
        main();
    }

    my_func(num);

    printf("\nnum = '%d', flag = '%d'\n\n", num, flag);
    return(0);
}
