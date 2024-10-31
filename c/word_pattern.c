#include <stdio.h>
#include <string.h>

int
wordPattern (char * pattern, char * s)
{
    int patt_len = 0;
    char *str = 0;
    char lukup_tbl[26][10] = { 0 };
    int i = 0;
    
    if ((pattern == NULL) && (s == NULL)) {
        return(1);
    } else if ((pattern == NULL) || (s == NULL)) {
        return(0);
    }
    
    patt_len = strlen(pattern);
    //memset(lukup_tbl, 0, sizeof(lukup_tbl));
    str = strtok(s, " ");
    
    for (i = 0; i < patt_len; i++) {
        printf("\n\nstr = '%s', lukup_tbl = '%s'\n\n",
               str, lukup_tbl[pattern[i] - 'a']);
        if (lukup_tbl[pattern[i] - 'a'] == NULL) {
            strcpy(lukup_tbl[pattern[i] - 'a'], str);
        } else if (strcmp(lukup_tbl[pattern[i] - 'a'], str) != 0) {
            printf("\n\nDBG :: Exited\n\n");
            return(0);
        }
        str = strtok(NULL, " ");
    }
    
    if (i < patt_len) {
        return(0);
    }
    
    return(1);
}

int
main (void)
{
    char *pattern = "abba";
    char s[] = "dog cat cat doc";

    printf("\n\nPattern = '%s', str = '%s', is_match = '%d'\n\n",
           pattern, s, wordPattern(pattern, s));

    return(0);
}
