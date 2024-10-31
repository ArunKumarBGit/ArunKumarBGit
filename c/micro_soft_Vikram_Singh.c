1)
200 bytes

0xCABF <- Search pattern
32-bit system & compiler

#define PATTERN             0xCABF
#define DBG_LOG             printf
#define INVALID_ARGUMENT    -1

int
get_pattern_cnt (const void *buffer_p, uint32_t sz)
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

        if (val == PATTERN) {
            cnt++;
            i++;    // Optimized
        }
    }

    return(cnt);
}


// 3 X 3 Matrix rotation
/*
    1 2 3
    4 5 6
    7 8 9

    7 4 1
    8 5 2
    9 6 3
*/

// Regular array
for (row = 0; row < row_sz; row++) {
    for (col = 0; col < col_sz; col++) {
        printf("%d", arr[row][col];
    }
    printf("\n");
}

// 90 degree rotation code
for (col = 0; col < col_sz; col++) {
    for (row = row_sz-1; row >= 0; row--) {
        printf("%d", arr[row][col]);
    }
    printf("\n");
}

