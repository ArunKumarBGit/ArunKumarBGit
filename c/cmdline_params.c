#include <stdio.h>

#define SUCCESS     0

int
main(int argc, char *argv[])
{
    int ret_val = SUCCESS;

    for (int i = 0; i < argc; i++) {
        printf("\nargv[%d] = '%s'\n\n", i, argv[i]);
    }

    return(ret_val);
}
