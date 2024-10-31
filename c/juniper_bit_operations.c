/*
 * unsigned int - 32 bits
 * Find set bits & return the count
 */


uint32_t
get_set_bits_count (uint32_t num)
{
    int cnt = 0;

    if (num == 0) {
        return(cnt);
    }

    while (num) {
        if (num & 0x1) {
            cnt++;
        }

        num /= 2;
    }

    return(cnt);
}


uint32_t
set_bit (uint32_t *num_p, uint32_t pos)
{
    if (num_p == NULL) {
        printf("Invalid parameter\n");
        return(SYSERR_INVALID_PARAM);
    }

    *num_p =| (1 << pos);
    return(SUCCESS);
}

uint32_t
clear_bit (uint32_t *num_p, uint32_t pos)
{
    if (num_p == NULL) {
        printf("Invalid parameter\n");
        return(SYSERR_INVALID_PARAM);
    }

    *num_p =& (~(1 << pos));
    return(SUCCESS);
}
