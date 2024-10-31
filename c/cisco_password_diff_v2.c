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
 *
 * Input: Password
 *        Pas$wrd#
 *
 * Output: 4
 *         2 characters got deleted from old password
 *         2 characters got added new in new password
 */

#define INVALID_PARAMS      -1

int 
getMinTotalNumChanges (char* oldPassStr, 
                       char* newPassStr) 
{
    int old_len = 0;
    int new_len = 0;
    int diff_len = 0;
    int i = 0;
    int j = 0;
    int cursor_i = 0;
    int cursor_j = 0;
    int absent = 0;
    
    if ((oldPassStr == NULL) || (newPassStr == NULL)) {
        printf("Invalid parameters\n");
        return(INVALID_PARAMS);
    }
    
    old_len = strlen(oldPassStr);
    new_len = strlen(newPassStr);
    diff_len = (old_len > new_len) ? (old_len - new_len) : (new_len - old_len);
    
    for (i = cursor_i; i < old_len; i++) {
        for (j = cursor_j; j < new_len; j++) {
            if ((oldPassStr[i] == newPassStr[j]) && (i == j)) {
                // Matching character found
                cursor_j = j+1;
                break;
            }
        }
        
        if (j == new_len) {
            absent++;
        }
    }    
    
    diff_len += (absent * 2);

    return(diff_len);
}

int main()
{
    char* oldPassStr = "Password";
    //char* newPassStr = "xyzxyzxx123";
    //char* newPassStr = "xyzxyzxP";
    char* newPassStr = "Pas$wrd#";

    printf("\nMininum total changes = '%d'\n\n", 
           getMinTotalNumChanges(oldPassStr, newPassStr));

    return 0;
}


