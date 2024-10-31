1 - write memcpy API

Typedef enum syserr_ {
 SYSERR_SUCCESS = 0,
 SYSERR_INV_PARAM = 1,
 SYSERR_NULL_PARAM = 2,
 SYSERR_MUTEX_LOCK_ERR = 3,
 SYSERR_UNMUTEX_LOCK_ERR = 4
} syserr_t;

syserr_t
my_memcpy (void *dest_p, void *src_p, uint32_t sz)
{
 char *d_p = (char *)dest_p;
 char *s_p = (char *)src_p;
 Uint32_t i = 0;

 If ((dest_p == NULL) || (src_p == NULL)) {
  printf(“NULL parameter passed for argument\n”);
  return(SYSERR_NULL_PARAM);
 }

If (sz == 0) {
  printf(“Invalid parameter passed for argument\n”);
  return(SYSERR_INV_PARAM);
}

for (i = 0; i < sz; i++) {
  d_p[i] = s_p[i];
}

return(SYSERR_SUCCESS);

}

# define WORD_SZ  4

syserr_t
my_memcpy_opt (void *dest_p, void *src_p, uint32_t sz)
{
 uint32_t *d_int_p = (uint32_t *)dest_p;
 uint32_t *s_int_p = (uint32_t *)src_p;
 char *d_p = NULL;
 char *s_p = NULL;
 uint32_t i = 0;
 uint32_t cnt = 0;

 If ((dest_p == NULL) || (src_p == NULL)) {
  printf(“NULL parameter passed for argument\n”);
  return(SYSERR_NULL_PARAM);
 }

If (sz == 0) {
  printf(“Invalid parameter passed for argument\n”);
  return(SYSERR_INV_PARAM);
}

// Copy at word boundary
cnt = sz/WORD_SZ;
for (i = 0; i < cnt; i++) {
  d_int_p[i] = s_int_p[i];
}

// Copy remaining bytes
d_p = (char *) (d_int_p + cnt);
s_p = (char *) (s_int_p + cnt);
cnt = sz%WORD_SZ;
for (i = 0; i < cnt; i++) {
  d_p[i] = s_p[i];
}

return(SYSERR_SUCCESS);

}

Source = 0x4000
Dest = 0x8000
Sz = 0x100

Source = 0x8001
Dest = 0x8000
Sz = 0x100

Source = 0x8000
Dest = 0x8001
Sz = 0x100

/*
 * If (src_addr > dest_addr), then copy from first byte & increment to next addr
 * If ((src_addr < dest_addr) && ((src_addr + sz) > dest_addr)), then copy from last byte & decrement to prev addr
 */ 


