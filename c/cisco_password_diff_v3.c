#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Complete the 'getMinTotalNumChanges' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING oldPassStr
 *  2. STRING newPassStr
 */

#define INVALID_PARAM   -1

int 
getMinTotalNumChanges (char* oldPassStr, char* newPassStr) 
{
    int old_len = 0;
    int new_len = 0;
    int diff_len= 0;
    int i       = 0;
    int j       = 0;
    int pos_j   = 0;
    int abs     = 0;
    int num_chg = 0;
    
    if ((oldPassStr == NULL) || (newPassStr == NULL)) {
        return(INVALID_PARAM);
    }
    
    old_len = strlen(oldPassStr);
    new_len = strlen(newPassStr);
    diff_len = (old_len < new_len) ? (new_len - old_len) : (old_len - new_len);
    
    for (i = 0; i < old_len; i++) {
        for (j = pos_j; j < new_len; j++) {
            if (oldPassStr[i] == newPassStr[j]) {
                // Exact match found. Progress to next char
                pos_j = j + 1;
                break;
            }
        }
        if (j == new_len) {
            abs++;  // Mismatch found
        }
    }
    
    if (old_len <= new_len){
        num_chg = diff_len + (abs * 2);
    } else {
        num_chg = diff_len + (2 * (abs - diff_len));
    }

    return(num_chg);

}

int main()
{
    char *oldPassStr = "password";
    char *newPassStr = "pss$w#rd";

    printf("\n\n old = '%s'\n new = '%s'\n diff = '%d'\n\n",
           oldPassStr, newPassStr, 
           getMinTotalNumChanges(oldPassStr, newPassStr));

    return 0;
}

