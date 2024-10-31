/*
 Given a dictionary of words and a string made up of those words (no spaces),
return the original sentence in a list.
If there is more than one possible reconstruction, return any of them.
If there is no possible reconstruction, then return null.

For example, given the set of words
'quick', 'brown', 'the', 'fox', and the string "thequickbrownfox",
you should return ['the', 'quick', 'brown', 'fox'].

Given the set of words 'bed', 'bath', 'bedbath', 'and', 'beyond', and the string "bedbathandbeyond",
return either ['bed', 'bath', 'and', 'beyond] or ['bedbath', 'and', 'beyond'].
 *
 * Expected output:
 	./a.out bedbathand bed bath and beyond 
     bed
     bath
     and
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define TRUE    1
#define FALSE   0

typedef enum syserr_ {
    SYSERR_SUCCESS  = 0,
    SYSERR_INVALID_ARG,
    SYSERR_MALLOC_FAILED,
} syserr_t;

syserr_t
get_sub_str (char *str_p, char *sub_str_p, unsigned int num_char)
{
    if ((str_p == NULL) || (sub_str_p == NULL) || (num_char == 0)) {
        printf("Invalid argument\n");
        return(SYSERR_INVALID_ARG);
    }

    strncpy(sub_str_p, str_p, num_char);
    sub_str_p[num_char] = '\0';

    return(SYSERR_SUCCESS);
}

bool hash_tbl[1000];

syserr_t
my_hash_add (char *str_p)
{
    unsigned int i          = 0;
    unsigned int len        = 0;
    unsigned int hash_id    = 0;

    if (str_p == NULL) {
        printf("Invalid argument\n");
        return(SYSERR_INVALID_ARG);
    }

    len = strlen(str_p);

    for (i = 0; i < len; i++) {
        hash_id += str_p[i];
    }

    hash_tbl[hash_id] = TRUE;

    return(SYSERR_SUCCESS);

}

syserr_t
my_hash_find (char *sub_str_p, bool *is_found_p)
{
    unsigned int i          = 0;
    unsigned int len        = 0;
    unsigned int hash_id    = 0;

    if ((sub_str_p == NULL) || (is_found_p == NULL)) {
        printf("Invalid argument\n");
        return(SYSERR_INVALID_ARG);
    }

    len = strlen(sub_str_p);

    for (i = 0; i < len; i++) {
        hash_id += sub_str_p[i];
    }

    *is_found_p = hash_tbl[hash_id];

    return(SYSERR_SUCCESS);
}

int
main (int argc, char *argv[])
{
    unsigned int i      = 0;
    unsigned int word_len   = 0;
    unsigned int str_len    = 0;
    unsigned int done_len   = 0;
    char *str_p             = NULL;
    char *sub_str_p         = NULL;
    bool start_bit          = TRUE;
    bool is_found           = FALSE;
    syserr_t    ret_val     = SYSERR_SUCCESS;

    // Build the library using hash table
	for (i = 2; i < argc; i++) {
        ret_val = my_hash_add(argv[i]);
        if (ret_val != SYSERR_SUCCESS) {
            printf("Hash add failed for '%s', ret_val = '%d'\n",
                   argv[i], ret_val);
            return(ret_val);
        }
    }

    // Lookup and print matching tokens
    word_len = strlen(argv[1]);
    str_p = argv[1];

    sub_str_p = (char *)malloc(word_len+1);
    if (sub_str_p == NULL) {
        printf("Malloc failed for sub_str_p\n");
        return(SYSERR_MALLOC_FAILED);
    }

    while (done_len < word_len) {
        if (start_bit == TRUE) {
            str_len = 1;
            start_bit = FALSE;
        }

        ret_val = get_sub_str(str_p, sub_str_p, str_len);
        if (ret_val != SYSERR_SUCCESS) {
            printf("Failed to get sub_str, str_len = '%d', ret_val = '%d'\n",
                   str_len, ret_val);
            return(ret_val);
        }

        ret_val = my_hash_find(sub_str_p, &is_found);
        if (ret_val != SYSERR_SUCCESS) {
            printf("my_hash_find failed for sub_str '%s', ret_val = '%d'\n",
                   sub_str_p, ret_val);
            return(ret_val);
        }

        if (is_found == TRUE) {
            printf("%s\n", sub_str_p);
            start_bit = TRUE;
            str_p += str_len;
            done_len += str_len;
        } else {
            str_len++;
        }
    }

    free(sub_str_p);

    return(ret_val);
}
