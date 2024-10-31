#include <stdio.h>
#include <ctype.h>

int main()
{
    int i = 0;

    printf("The ASCII value of all control characters are:\n");
    for (i = 0; i <= 127; ++i)
    {
        if (iscntrl(i)) {
            printf("%d ", i);
        }
    }

    printf("\n\n");
    return (0);
}

