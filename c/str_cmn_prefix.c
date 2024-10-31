#include <stdio.h>
#include <string.h>

char cmn_prefix[200];

char * longestCommonPrefix (char ** strs, int strsSize) 
{
    int ref_len = 0;
    int len[200] = {0};
    int i = 0;
    int cursor = 0;
    char ch;
    
    for (i = 0; i < strsSize; i++) {
        len[i] = strlen(strs[i]);
    }
    
    while (cursor < len[0]) {
        ch = strs[0][cursor];
        printf("\ncursor = '%d', ch = '%c'\n", cursor, ch);
        for (i = 0; i < strsSize; i++) {
            if (cursor >= len[i]) {
                return(cmn_prefix);
            } 
            
            if (ch != strs[i][cursor]) {
                return (cmn_prefix);
            }
        }
        cmn_prefix[cursor] = ch;
        cursor++;
    }
    
    return(cmn_prefix);
}

int
main (void) 
{
    char *str[] = {"flower", "flow", "flight"};
    printf("\nCommon prefix = '%s'\n\n", longestCommonPrefix(str, 3));
    return(0);
}
