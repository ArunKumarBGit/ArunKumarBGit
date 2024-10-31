#include <stdio.h>
#include <string.h>

int
is_isomorphic (char * s, char * t) 
{
    //int lukup_tbl[256] = {[0 ... 255] = -1};
    int lukup_tbl[256] = {-1};
    char used_tbl[256] = {[0 ... 255] = -1};
    int len_s = 0;
    int len_t = 0;
    int i = 0;
    
    if ((s == NULL) && (t == NULL)) {
        return(1);
    } else if ((s == NULL) || (t == NULL)) {
        return(0);
    }
    
    len_s = strlen(s);
    len_t = strlen(t);
    
    if (len_s != len_t) {
        printf("\nlen_s = '%d', len_t = '%d'\n",
               len_s, len_t);
        return(0);
    }
    
    printf("\nlukup_tbl[0] = '%d', used_tbl[0] = '%d'\n", 
           lukup_tbl[2], used_tbl[1]);
    for (i = 0; i < len_s; i++) {
        if ((lukup_tbl[s[i]] == -1) && (used_tbl[t[i]] == -1)) {
            lukup_tbl[s[i]] = t[i];
            used_tbl[t[i]] = 1;
            printf("\nDBG :: assigned\n");
        } else if ((lukup_tbl[s[i]] != -1) && (used_tbl[t[i]] == -1)) {
            printf("\n1 :: lukup_tbl[s[%d]] = '%c', t[%d] = '%c'\n",
                   i, lukup_tbl[s[i]], i, t[i]);
            return(0);
        } else if ((lukup_tbl[s[i]] == -1) && (used_tbl[t[i]] != -1)) {
            printf("\n2 :: lukup_tbl[s[%d]] = '%c', t[%d] = '%c'\n",
                   i, lukup_tbl[s[i]], i, t[i]);
            return(0);
        }
        
        if (lukup_tbl[s[i]] != t[i]) {
            printf("\n3 :: lukup_tbl[s[%d]] = '%c', t[%d] = '%c'\n",
                   i, lukup_tbl[s[i]], i, t[i]);
            return(0);
        }
    }
    
    return(1);
}

int
main (void)
{
    char *s = "egg";
    char *t = "add";

    printf("\n\ns = '%s', t = '%s', is_isomorphic = '%d'\n\n",
           s, t, is_isomorphic(s, t));
    return(0);
}
