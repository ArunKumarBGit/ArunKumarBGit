// Vikram Singh
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define PATTERN             0xCABF
#define DBG_LOG             printf
#define INVALID_ARGUMENT    -1

int
get_pattern_cnt (const void *buffer_p, uint32_t sz, uint32_t *loop_cnt_p)
{
    int i = 0;
    int cnt = 0;
    const char *buf_p = buffer_p;
    uint16_t val = 0;

    if ((buf_p == NULL) || (sz == 0)) {
        DBG_LOG("Invalid parameter\n");
        return(INVALID_ARGUMENT);
    }

    for (i = 0; i+1 < sz; i++) {        
        // If it is 16 bit aligned, then loop size reduces by half 
        // Only the even number offset is read
        // buf_f --> 00 00 CA BF 00 00
        // buf_f --> 00 CA BF 00 00
        val = *(uint16_t *) (buf_p + i);
        printf("\nDBG :: val = '0x%x', i = '%d'", val, i);

        if (val == PATTERN) {
            cnt++;
            i++;    // Optimized
            (*loop_cnt_p)++;
        }
    }

    return(cnt);
}

int
main (void)
{
    char buf[]          = "0000CABF0000CABF";
    uint32_t loop_cnt   = 0;
    uint32_t sz         = 0;
    uint32_t cnt        = 0;

    sz = strlen(buf);
    cnt = get_pattern_cnt(buf, sz, &loop_cnt);

    printf("\nbuf = '%s', sz = '%d', pattern_cnt = '%d', loop_cnt = '%d'\n\n",
           buf, sz, cnt, loop_cnt);

    char val[5] = { 0 };
    loop_cnt = 0;
    cnt = 0;
    for (int i = 0; i+1 < sz; i++) {        
        // If it is 16 bit aligned, then loop size reduces by half 
        // Only the even number offset is read
        // buf_f --> 00 00 CA BF 00 00
        // buf_f --> 00 CA BF 00 00
        strncpy(val, buf+i, 4);
        printf("\nDBG :: val = '%s', i = '%d'", val, i);

        if (strncmp(val, "CABF", 4) == 0) {
            cnt++;
            i+=3;    // Optimized
        }
        loop_cnt++;
    }

    printf("\nbuf = '%s', sz = '%d', pattern_cnt = '%d', loop_cnt = '%d'\n\n",
           buf, sz, cnt, loop_cnt);


    return(0);
}
