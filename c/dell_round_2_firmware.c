/*
 * Write a Macro, to clear a given bit
 */
#define CLEAR_BIT(num, bit) (num & (~(1 << bit)))

/*
 * Function ptr needed
 *  i/p: void
 *  o/p: int
 */

typedef int (*my_func_p) (void);

/*
 * Producer <--> Circular Buf 2K  :: 1K data + 1K metadata <--> Consumer
 */ 
