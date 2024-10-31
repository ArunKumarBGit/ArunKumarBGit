#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SUCCESS             0
#define printf(msg, ...)    printf("\n"msg"\n", ##__VA_ARGS__)

int
get_slot_port_num (const char *str, int *slot_p, int *port_p)
{
    char intf[20];
    char *ptr = NULL;
    int ret_val = SUCCESS;

    strcpy(intf, str);

    ptr = strtok(intf, "/");
    *slot_p = atoi(ptr+2);

    ptr = strtok(NULL, "/");
    *port_p = atoi(ptr);

    return(ret_val);
}

int
main (void)
{
    char intf[20]   = "fc4/9";
    int slot        = 0;
    int port        = 0;
    int ret_val     = SUCCESS;

    ret_val = get_slot_port_num(intf, &slot, &port);
    if (ret_val != SUCCESS) {
        printf("Failed!");
    } else {
        printf("Slot = '%d', port = '%d'\n", slot, port);
    }

    return(ret_val);
}
