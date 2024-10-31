#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
isPalindrome (char * s)
{
    long int len = 0;
    long int str_len = 0;
    char *str = NULL;
    long int i = 0;
    long int j = 0;

    if (s == NULL) {
        printf("Invalid parameter\n");
        return (0);
    }

    len = strlen(s) + 1;
    str = (char *)malloc(len);
    memset(str, 0, len);

    for (i = 0; i < len; i++) {
        if (((s[i] >= 'a') && (s[i] <= 'z')) ||
            ((s[i] >= '0') && (s[i] <= '9'))) {
            str[j++] = s[i];
        } else if ((s[i] >= 'A') && (s[i] <= 'Z')) {
            str[j++] = 'a' + (s[i] - 'A');
        }
    }

    str_len = strlen(str);
    if (str_len == 0) {
        free(str);
        return(1);
    }
    printf("\nDigested word: '%s'\n", str);

    for (i = 0, j = str_len-1; i < j; i++, j--) {
        if (str[i] != str[j]) {
            free(str);
            return(0);
        }
    }
    free(str);
    return(1);
}

int
main (void) {
    char *s = "A man, a plan, a canal: Panama";

    printf("\nIs '%s' Palindrom?\n\n'%s'\n\n", s, 
            (isPalindrome(s) ? "TRUE" : "FALSE") );

    return(0);
}
