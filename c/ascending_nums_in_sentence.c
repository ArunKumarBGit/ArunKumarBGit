#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS             0
#define printf(msg, ...)    printf("\n"msg"\n", ##__VA_ARGS__)

int
areNumbersAscending  (char * s) 
{
    char *word = NULL;
    int num = 0;
    int val = 0;
    
    printf("%s", s);

    word = strtok(s, " ");
    
    while (word != NULL) {
        printf("%s", word);

        val = atoi(word);
        if (val != 0) {
            if (num < val) {
                num = val;
            } else {
                return(0);
            }
        }
        word = strtok(NULL, " ");
    }
    
    return(1);
}

int
main (void)
{
    char str[] = "hello world 5 x 5";
    int ret_val = SUCCESS;

    areNumbersAscending(str);

    return(ret_val);
}
