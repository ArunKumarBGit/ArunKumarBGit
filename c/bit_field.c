#include <stdio.h>

// A structure without forced alignment
typedef struct test1 {
    unsigned int x : 5;
    unsigned int y : 3;
} test1_t;

// A structure with forced alignment
typedef struct test2 {
    unsigned int x : 5;
    unsigned int : 0;
    unsigned int y : 8;
} test2_t;

typedef union test3_ {
    test1_t num1;
    int num2;
} test3_t;

int
main (void)
{
    test3_t val = {0};

    printf("\nsizeof(test1_t) = '%lu', sizeof(test2_t) = '%lu', "
           "sizeof(test3_t) = '%lu'\n",
           sizeof(test1_t), sizeof(test2_t), sizeof(test3_t));

    val.num1.x = 0x1E;
    val.num1.y = 0x7;

    printf("\nunion val = '0x%X'\n\n", val.num2);

    return(0);
}
