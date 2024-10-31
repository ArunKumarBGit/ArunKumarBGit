#include <stdio.h>

#define SUCCESS         0

typedef union _mix {
    int i;
    char c;
    float f;
} mix_t;


int
main(void)
{
    int ret_val = SUCCESS;
    static __thread mix_t m[4] = {{4}, {.f = 9.4}, 
                                  {.f = 4.5}, [3] = {94} };

    printf("m[1].i = '%d'\n", (int)m[1].f);
    printf("m[3].c = '%d'\n", m[3].c);

    return(ret_val);
}
