[1]
/*
 * Array, ptr to string,
 * char *arr[]
 * fn - copy string & return
 */
typedef enum syserr_ {
    SYSERR_SUCCESS          = 0,
    SYSERR_INVALID_PARAM    = 1,
    SYSERR_MAX              = 2
} syserr_t;

syserr_t
duplicate_str_array (char **src_arr, unsigned int sz, char ***dst_arr)
{
    int i = 0;
    unsigned in str_len = 0;

    if ((src_arr == NULL) || (sz == 0) || (dst_arr == NULL)) {
        printf("Invalid parameter\n");
        return(SYSERR_INVALID_PARAM);
    }

    *dst_arr = (char **)malloc(sz * sizeof(char *));
    // Assume malloc is successful

    for (i = 0; i < sz; i++) {
        str_len = strlen(src_arr[i]);

        (*dst_arr)+i = (char *)malloc(str_len+1);

        strcpy((*dst_arr)+i, *src_arr[i]);
    }
}

// char *src_arr[] = {"STR_1", "STR_2"..};
// char **dst_arr = NULL;
// sz = 
// duplicate_str_array(src_arr, 10, &dst_arr);


[2]
// Array of int
// Target sum
// Fn - TRUE :: Any two int sum == Target
//    - FALSE, otherwise


{1, 3, 5, 7},  8;  1 + 3, 1 + 5, 1 + 7  --> TRUE
                          3 + 5, 3 + 7
                                 5 + 7
// Use Hash table:
//  Take the first element from hash table
//  Subtract its value from the Target
//  Check if any value present on that location of hash table


[3]
// Str1, Str2
// Anagram check function  :: ABC == BAC == CBA

AABC --> lukup_tbl_1['A']++;
CABA --> lukup_tbl_2['C']++;       check != 0 & lukup_tbl_1['C']--;

loop & check if lukup_tbl_1 == lukup_tbl_2


syserr_t
is_anagram (char *str_1, char *str_2, uint8_t *is_anagram_p)
{
    char lukup_tbl[256] = {0};
    unsigned int len_1 = 0;
    unsigned int len_2 = 0;
    int i = 0;

    // Assume all parameters check passed (not NULL)

    // Assume string sizes are not '0'

    len_1 = strlen(str_1);
    len_2 = strlen(str_2);

    if (len_1 != len_2) {
        *is_anagram_p = FALSE;
        return(SYSERR_SUCCESS);
    }

    for (i = 0; i < len_1; i++) {
        lukup_tbl[str_1[i]]++;
    }

    for (i = 0; i < len_1; i++) {
        if (lukup_tbl[str_2[i]] == 0) {
            *is_anagram_p = FALSE;
            return(SYSERR_SUCCESS);
        }
        lukup_tbl[str_2[i]]--;
    }

    *is_anagram_p = TRUE;
    return(SYSERR_SUCCESS);
}
