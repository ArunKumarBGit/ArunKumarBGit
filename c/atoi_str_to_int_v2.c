#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int
myAtoi (char * s)
{
    int len = 0;
    int i = 0;
    char sign = 1;
    char sign_set = 0;
    char num_started = 0;
    long int val = 0;
    int temp_val = 0;
    int max_positive = 0x7FFFFFFF;
    int max_negative = 0x80000000;

    if (s == NULL) {
        return(0);
    }

    len = strlen(s);

    for (i = 0; i < len; i++) {
        // Identify leading space
        if ((s[i] == ' ') && (num_started == 0) && (sign_set == 0)) {
            continue;
        } else if ((s[i] == ' ') &&
                   ((num_started == 1) || (sign_set == 1))) {
            break;
        }

        // Identify sign
        if ((s[i] == '+') && (num_started == 0) && (sign_set == 0)) {
            sign = 1;
            sign_set = 1;
            continue;
        } else if ((s[i] == '+') &&
                   ((num_started == 1) || (sign_set == 1))) {
            break;
        }

        if ((s[i] == '-') && (num_started == 0) && (sign_set == 0)) {
            sign = -1;
            sign_set = 1;
            continue;
        } else if ((s[i] == '+') &&
                   ((num_started == 1) || (sign_set == 1))) {
            break;
        }

        temp_val = s[i] - '0';
        if ((temp_val >= 0) && (temp_val <= 9)) {
            if (val > (long)max_positive + 1) {
                break;
            }
            val = (val * 10) + temp_val;
            num_started = 1;
            continue;
        } else {
            break;
        }
    }

    if ((sign == 1) && (val > max_positive)) {
        val = max_positive;
    } else if ((sign == -1) && (val > ((long)max_positive + 1))) {
        val = max_negative;
    } else {
        val = sign * val;
    }

    return(val);
}


int
main (void)
{
    char *s = "   -49";

    printf("\n\ns = '%s', val = '%d'\n\n", s, myAtoi(s));

    return(0);
}
