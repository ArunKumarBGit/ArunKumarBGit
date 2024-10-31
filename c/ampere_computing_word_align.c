/*
struct temp {
    pragma pack 1;
    int a;  //0x1000
    char b; //0x1004
    inc c;  //0x1005
    char d; //0x1009
} __attribute((packed));
*/

#include <stdio.h>

struct temp my_temp;

my_temp.c = 0x10;

int a = my_temp.c;


#define     MASK_BYTE_0     0x000000FF
#define     MASK_BYTE_1     0x0000FF00
#define     MASK_BYTE_2     0x00FF0000
#define     MASK_BYTE_3     0xFF000000
#define     MASK_3_MSB      0xFFFFFF00

unsigned int
rd_struct_mbr(void *ptr, unsigned int cnt)
{
    unsigned int val        = 0;
    unsigned int deviation  = 0;
    unsigned int pre_val    = 0;
    unsigned int nxt_val    = 0;
    unsigned int pre_byte_cnt   = 0;
    unsigned int nxt_byte_cnt   = 0;

    deviation = ptr % 4;

    // If word aligned
    if (deviation == 0) {
        return (*(unsigned int *)ptr);
    }

    // If not aligned
    pre_val = *(((char *)ptr) - deviation);
    nxt_val = *(((unsigned int *)pre_val) + 1);

    pre_byte_cnt = 4 - deviation;
    nxt_byte_cnt = 4 - pre_byte_cnt;

    if (deviation == 1) {
        val = (pre_val & MASK_3_MSB) >> 8;
        val |= ((nxt_val & MASK_BYTE_0) << 24);
    }
    
    return (val);
}
