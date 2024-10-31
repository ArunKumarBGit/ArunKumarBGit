#include <stdio.h>

typedef struct  {
    int type;
    int len;
    char val[0];    // Size is not counted by compiler
} tlv_t;

int
main (void)
{
    char c[0];
    printf("\nsizeof(tlv_t) = '%lu', sizeof(c) = '%lu'\n\n", 
           sizeof(tlv_t), sizeof(c));
    return(0);
}
