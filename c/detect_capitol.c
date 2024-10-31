#include <stdio.h>
#include <string.h>

#define MAX_DIFF_CAPITAL   26
#define is_capital(c)      (((c - 'A') <= MAX_DIFF_CAPITAL) ? 1 : 0);

char
is_valid_str (char *str)
{
    char len = 0;
    char i = 0;
    char cap = 0;
    char all_cap = 0;
    char all_small = 0;
    char first_cap = 0;
    char found_cap = 0;
    char found_small = 0;

    len = strlen(str);

    for (i = 0; i < len; i++) {
        cap = is_capital(str[i]);

        if (cap == 1) {
            found_cap = 1;

            if (i == 0) {
                first_cap = 1;
            } else {
                if (((first_cap != 1) && (all_cap != 1)) ||
                     (all_small == 1) || (found_small == 1)) {
                    return(0);
                } else if ((first_cap == 1) && (i == 1)) {
                    first_cap = 0;
                    all_cap = 1;
                } else if ((first_cap == 1) && (all_cap == 0) && (i > 1)) {
                    return(0);
                }
                else if (all_cap == 1) {
                    if (found_small && all_small) {
                        return(0);
                    }
                }
            }
        } else {
            found_small = 1;

            if (i == 0) {
                all_small = 1;
            }

            if (all_cap == 1) {
                return(0);
            }
        }
    }

    return(1);
}

char
detectCapitalUse (char * word)
{
    char *str = NULL;
    char ret_val = 0;

    if (word == NULL) {
        return(1);
    }

    str = strtok(word, " ");

    while (str != NULL) {
        ret_val = is_valid_str(str);
        if (ret_val == 0) {
            return(ret_val);
        }

        str = strtok(NULL, " ");
    }

    return(ret_val);
}

int
main (void)
{
    char *str = "USA";

    printf("\n\nWord = '%s', detectCapitalUse = '%d'\n\n", 
           str, detectCapitalUse(str));
    return(0);
}
