/*
 * Six protocols
 * switch-case per protocol
 * bit wise operator
 *
 */

#define PROTOCOL_1_MASK 0x0001
#define PROTOCOL_2_MASK 0x0002
#define PROTOCOL_3_MASK 0x0004
#define PROTOCOL_4_MASK 0x0008
#define PROTOCOL_5_MASK 0x0010
#define PROTOCOL_6_MASK 0x0020

#define IS_PROTOCOL_1_SET(val)  ((val) & PROTOCOL_1_MASK)

typedef struct proto_id_ {
    uint32_t proto_1:1;
    uint32_t proto_2:1;
    uint32_t proto_3:1;
    uint32_t proto_4:1;
    uint32_t proto_5:1;
    uint32_t proto_6:1;
} proto_id_t;

typedef enum proto_id_enum_ {
    PROTO_ID_1  = 0,
    PROTO_ID_2, 
    PROTO_ID_3,
    PROTO_ID_4,
    PROTO_ID_5,
    PROTO_ID_6,
    PROTO_ID_MAX
} proto_id_enum_t;

#define IS_PROTOCOL_1_SET(val)  ((val) & (1 << PROTO_ID_1))
#define IS_PROTOCOL_2_SET(val)  ((val) & (1 << PROTO_ID_2))
#define IS_PROTOCOL_3_SET(val)  ((val) & (1 << PROTO_ID_3))
#define IS_PROTOCOL_4_SET(val)  ((val) & (1 << PROTO_ID_4))
#define IS_PROTOCOL_5_SET(val)  ((val) & (1 << PROTO_ID_5))
#define IS_PROTOCOL_6_SET(val)  ((val) & (1 << PROTO_ID_6))

#define IS_PROTOCOL_SET(val, proto_id)          ((val) & (1 << PROTO_ID_##proto_id))
#define PROTOCOL_SET(val, proto_id)             ((val) | (1 << PROTO_ID_##proto_id))
#define UNIQUE_PROTOCOL_SET(val, proto_id)      { (val) = 0; \
                                                  ((val) | (1 << PROTO_ID_##proto_id)); }
#define PROTOCOL_RESET(val, proto_id)           ((val) & ~(1 << PROTO_ID_##proto_id))
#define IS_ALL_PROTOCOL_SET(val)                ((~(val & <TODO>)) ? FALSE : TRUE )

#define WORD_SZ                      8
uint32_t
get_num_protocol_set (uint32_t val) 
{
    uint32_t cnt = 0;

    if (val == 0) {
        return(0);
    }

    while(val) {
        if (val & 0x1) {
            cnt++;
        }
        val >>= 1;
    }

    return(cnt);
}

syserr_t
unit_test_1 (uint32_t val, 
             proto_id_enum_t set_proto, 
             proto_id_enum_t reset_proto, 
             uint32_t *num_proto_set_p)
{
    if (num_proto_set_p == NULL) {
        printf("Invalid parameter\n");
        return(SYSERR_INVALID_PARAM);
    }

    printf("Input val = '%d'\n", val);
    printf("Is PROTO_ID_4 set = '%s'\n", 
           (IS_PROTOCOL_SET(val, PROTO_ID_4)? "TRUE":"FALSE"));

}

syserr_t
is_protocol_set(void *val_p, proto_id_enum_t proto_id, uint8_t *is_set_b)
{
    char *buf_p = (char *)val_p;

    // Param NULL check & reporting/ returning

    uint32_t word_cnt = 0;
    uint32_t bit_pos = 0;

    // proto_id = 25
    word_cnt = proto_id / WORD_SZ; // 3
    bit_pos = proto_id % WORD_SZ;  // 1

    // Reach to the target byte
    buf_p += word_cnt;

    return((*buf_P) & (0x1 << bit_pos));
}

int
main (void)
{
    uint32_t val = 0;


    printf("val = '0x%x'\n", val);

    val = PROTOCOL_SET(val, PROTO_ID_1);
    val = PROTOCOL_SET(val, PROTO_ID_5);

    printf("val = '0x%x', num_protocol_set = '%d'\n", val,
           get_num_protocol_set(val));

    return(0);
}
