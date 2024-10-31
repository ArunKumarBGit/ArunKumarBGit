#include <stdio.h>
#include <string.h>

#define SUCCESS     0

void
print_vble_name_optional(const char *);

int
main(void)
{
    char str[] = "\nVariable name is optional\n\n";
    int ret_val = SUCCESS;

    print_vble_name_optional(str);

    return(ret_val);
}

void
print_vble_name_optional(const char *str)
{
    printf("%s", str);
}
