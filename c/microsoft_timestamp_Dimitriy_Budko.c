#include <stdio.h>
#include <stdint.h>
// 1 GHz 64-bit timer, increments by 1 every 1ns, starts from 0 on reset. 

// read low 32 bits
uint32_t rl (void)
{
    return(0x11223344);
}

// read high 32 bits
uint32_t rh(void)
{
    return(0xAABBCCDD);
}

#define MAX_LOOP_COUNT  1 //1000
#define OVERFLOW_LIMIT  0xFFFFFFFF

// implement 64-bit timestamp function using the above two APIs
uint64_t timestamp(void) {
    uint64_t t64 = 0;
    uint32_t tlow32 = 0;
    uint32_t h1 = 0, h2 = 0;
    uint64_t thi32 = 0;

#if 0 // Arun Kumar B solution to handle overflow
    tlow32 = rl();

    // Handle overflow in the lower 32 bit timestamp
    if (tlow32 >= (OVERFLOW_LIMIT/100)) {
        tlow32 = rl();
    }
    thi32 = rh();
#endif

    // Solution by Dimitriy_Budko
    do {
        h1 = rh();
        tlow32 = rl();
        h2 = rh();
    } while (h1 != h2);

    thi32 = h1;

    t64 = (thi32 << 32) | tlow32;

    return(t64);
}

// Unit Test to validate the timestamp
int main(void) {
    int i = 0;
    uint64_t curr_ts = 0;
    uint64_t prev_ts = 0;

    prev_ts = timestamp();

    for (i = 0; i < MAX_LOOP_COUNT; i++) {
        curr_ts = timestamp();

        if (curr_ts <= prev_ts) {
            printf("Current timestamp '0x%llx' is smaller/ equal to previous "
                   "timestamp '0x%llx'\n", curr_ts, prev_ts);
        }
        
        prev_ts = curr_ts;
        
        printf("Count '%d', timestamp '0x%llx'\n", i, curr_ts);
    }

    return (0);
}
