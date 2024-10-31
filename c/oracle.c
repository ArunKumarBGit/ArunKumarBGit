//ABCA --> A 2, B 1, C 1 

#include <stdio.h>

#define SUCCESS         0

unsigned int
sizeof_str (const char *str)
{
    unsigned int size = 0;

    if (str == NULL) {
        printf("Invalid argument\n");
    }

    while (str[size] != '\0') {
        size++;
    }

    return(size + 1);
}

void
print_chr_cnt (const char *str)
{
    static unsigned int arr[256];
    unsigned int len = 0;
    unsigned int offset = 0;
    unsigned int i = 0;

    if (str == NULL) {
        printf("Invalid argument\n");
    }

    len = sizeof_str(str);

    for (i = 0; i < len-1; i++) {
        offset = str[i];
        arr[offset]++;
    }

    arr[90]++;
    arr['Z']++;

    for (i = 0; i < 256; i++) {
        if (arr[i]) {
            printf("ASCII '%d', char '%c', count '%d'\n", i, (char)i, arr[i]);
        }
    }
}

int
main (void)
{
    char str[] = "ABCAaabcaa";
    
    print_chr_cnt(str);

    return(SUCCESS);
}
