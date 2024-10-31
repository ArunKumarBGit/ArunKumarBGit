#include <stdio.h>
#include <string.h>



int
strStr (char * haystack, char * needle)
{
    unsigned long int haystack_len = 0;
    unsigned long int needle_len = 0;
    unsigned long int i = 0;
    unsigned long int j = 0;
    int pos = -1;
    int ret_val = -1;

    if (needle == NULL) {
        return(0);
    }

    if (haystack == NULL) {
        return(ret_val);
    }

    haystack_len = strlen(haystack);
    needle_len = strlen(needle);

    if (needle_len == 0) {
        return(0);
    }

    if (haystack_len < needle_len) {
        return(ret_val);
    }

    for (i = 0, j = 0; j < haystack_len; j++, i = 0) {
        if (needle[i] == haystack[j]) {
            pos = j;
            while ((needle[i] != '\0') && (haystack[j] != '\0')) {
                i++;
                j++;
                if ((i < needle_len) && (needle[i] != haystack[j])) {
                    j = pos;
                    pos = -1;

                    if ((haystack_len - (j + 1)) < needle_len) {
                        return(ret_val);
                    }
                    break;
                }
            }
            if (pos != -1) {
                return(pos);
            }
        }
    }

    return(ret_val);
}


int
main (void) 
{
    char haystack[] = "mississippi";
    char needle[] = "issip";

    printf("\n\nReturn value from strStr() = '%d'\n\n", 
           strStr(haystack, needle));

    int ret_val = 0;

    return(ret_val);
}
