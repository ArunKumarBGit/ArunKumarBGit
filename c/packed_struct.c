#include <stdio.h>
#include <stdlib.h>

#define SUCCESS             0
//#define printf(msg, ...)    printf("\n"msg"\n", ##__VA_ARGS__)
#define printf(format, args...)    printf("\n"format"\n", ##args)

typedef struct packed_struct_ {
    int i;
    char c;
} __attribute__((packed)) packed_struct_t; 

typedef struct __attribute__((packed)) packed_struct2_ {
    int i;
    char c;
    short int si;
} packed_struct2_t; 

int
main (void)
{
    int ret_val = SUCCESS;

    printf("sizeof(packed_struct_t) = '%ld'", sizeof(packed_struct_t));
    printf("sizeof(packed_struct2_t) = '%ld'", sizeof(packed_struct2_t));

    return(ret_val);
}
