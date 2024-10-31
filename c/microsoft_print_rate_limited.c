#include <stdio.h>

#define my_log              printf
#define uart_print          printf
#define UART_MAX_CREDIT     5000
#define TRUE                1
#define FALSE               0


typedef enum syserr_ {
    SYSERR_SUCCESS      = 0,
    SYSERR_INVALID_ARG  = 1,

    // Add new ones above
    SYSERR_MAX = SYSERR_INVALID_ARG + 1
} syserr_t;

uint32_t uart_credits = 0;

uint32_t
get_credits_returned (uint64_t curr_time, uint64_t prev_time)
{
    // More checks here

    uint64_t diff_time = 0;

    diff_time = curr_time - prev_time;

    // For every 100 us, 1 credit is returned
    credits_returned = (UART_MAX_CREDIT/(1000000)) * diff_time;

    return(credits_returned);
}


syserr_t
print_rate_limited (char *str) 
{
    static uint64_t prev_time = 0;
    uint64_t curr_time = 0;
    uint32_t credits_returned = 0;
    static bool was_credits_zero = FALSE;

    if (str == NULL) {
        my_log("Invalid parameter passed\n");
    }

    curr_time = get_current_time();

    credits_returned = get_credits_returned(curr_time, prev_time);

    uart_credits += credits_returned;
    if (uart_credits > UART_MAX_CREDIT) {
        uart_credits = UART_MAX_CREDIT; // Handle credit overflow case
    }

    if (uart_credits > 0) {
        if (was_credits_zero == TRUE) {
            uart_print("...");
            was_credits_zero = FALSE;
        }
        uart_print("%s\n", str);
        uart_credits--;
    } else {
        was_credits_zero = TRUE;
    }

    prev_time = curr_time;

    return(SYSERR_SUCCESS);
}
