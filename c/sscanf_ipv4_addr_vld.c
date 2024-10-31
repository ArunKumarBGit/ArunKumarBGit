#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS             0
#define TRUE                1
#define FALSE               0
#define printf(msg, ...)    printf("\n"msg"\n", ##__VA_ARGS__)

int
main (void)
{
    char ipv4_addr[] = "10.107.127.44";
    char frag[4][5] = {0};
    char tst[4][5] = {0};
    int val = 0;
    int len = 0;
    int is_valid = TRUE;
    int i = 0;

    int ret_val = SUCCESS;

    printf("Enter IPv4 address: ");
    scanf("%[^.].%[^.].%[^.].%s", tst[0], tst[1], tst[2], tst[3]);
    printf("IP is %s;%s;%s;%s", tst[0], tst[1], tst[2], tst[3]);

    sscanf(ipv4_addr, "%[^.].%[^.].%[^.].%s",
           frag[0],frag[1],frag[2],frag[3]);

    printf("ipv4_addr = '%s', frag[0] = '%s', frag[1] = '%s', "
            "frag[2] = '%s', frag[3] = '%s'\n",
           ipv4_addr, frag[0], frag[1], frag[2], frag[3]);

    for (i = 0; i < 4; i++) {
        len = strlen(frag[i]);
        val = atoi(frag[i]);

        switch(len) {
            case 1:
            if (val == 0) {
                printf("Invalid IP, position '%d', value '%s'", i+1, frag[i]); 
                is_valid = FALSE;
            }
            break;

            case 2:
            if ((val < 10) || (val > 99)) {
                printf("Invalid IP, position '%d', value '%s'", i+1, frag[i]); 
                is_valid = FALSE;
            }
            break;

            case 3:
            if ((val < 100) || (val > 255)) {
                printf("Invalid IP, position '%d', value '%s'", i+1, frag[i]); 
                is_valid = FALSE;
            }
            break;

            default:
                printf("Invalid IP, position '%d', value '%s'", i+1, frag[i]); 
                is_valid = FALSE;
                break;
        }
    }

    if (is_valid) {
        printf("Valid IP: %s\n", ipv4_addr);
    }

    return(ret_val);
}
