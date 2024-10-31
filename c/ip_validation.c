#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SUCCESS                 0
#define IP_VALID                1
#define IP_INVALID              0
#define printf(msg, ...)        printf("\n"msg"\n", ##__VA_ARGS__)
typedef char bool;

#define DELIMITER               "."
#define STD_IP_PARTITION_COUNT  3

bool
is_part_valid (const char *str)
{
    unsigned int num = 0;
    unsigned int len = 0;

    len = strlen(str);
    num = atoi(str);

    printf("DBG :: str = '%s', len = '%d', num = '%d'",
           str, len, num);

    if ((len == 0) || (len > 3) || (num == 0) || (num > 255)) {
        return(IP_INVALID);
    }

    // Leading zeros are invalid
    switch (len) {
        case 2:
            if (num < 10) {
                return(IP_INVALID);
            }
        break;

        case 3:
            if ((num < 100) || (num > 255)) {
                return(IP_INVALID);
            }
        break;
    }

    return(IP_VALID);
}

bool
is_ip_valid (const char *ip_str)
{
    unsigned int len    = 0;
    unsigned int i      = 0;
    unsigned int part   = 0;
    unsigned int cnt    = 0;
    char str[20];
    char *temp_str_p    = NULL;
    unsigned int num    = 0;
    bool is_vld         = IP_INVALID;

    len = strlen(ip_str);

    // Confirm three partitions
    for (i = 0; i < len; i++) {
        if (ip_str[i] == '.') {
            part++;
        }
    }

    if (part != STD_IP_PARTITION_COUNT) {
        return (IP_INVALID);
    }

    strcpy(str, ip_str);

    temp_str_p = strtok(str, DELIMITER);
    if (temp_str_p == NULL) {
        return (IP_INVALID);
    }

    while (temp_str_p != NULL) {
        cnt++;
        is_vld = is_part_valid(temp_str_p);
        if (is_vld == IP_INVALID) {
            return (is_vld);
        }

        temp_str_p = strtok(NULL, DELIMITER);
        if ((temp_str_p == NULL) && (cnt != 4)) {
            return (IP_INVALID);
        }
    }

    return(IP_VALID);
}

int
main (void)
{
    char ip_str[] = "10.78.107.44.";
    int ret_val = SUCCESS;

    printf("%s is %s", ip_str, 
                       (is_ip_valid(ip_str) ? "VALID" : "_INVALID_"));

    return(ret_val);
}
