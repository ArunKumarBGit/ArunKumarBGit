#include <stdio.h>

#define SUCCESS             0
#define printf(msg, ...)    printf("\n"msg"\n", ##__VA_ARGS__)

int
main (void)
{
    int arr[4] = {0, 0, 0, 0};
    int ret_val = SUCCESS;

    printf("Enter four integers: ");
    scanf("%d %d", &arr[0], &arr[1]);
    scanf("%d", &arr[2]);
    scanf("%d", &arr[3]);

    printf("Here's the data: %d %d %d %d",
           arr[0], arr[1], arr[2], arr[3]);

    printf("Enter two integers: ");
    scanf("%d;%d", &arr[0], &arr[1]);
    printf("Here's the data: %d %d",
           arr[0], arr[1]);

    scanf("No text allowed here: %d\n\t", &arr[0]);

    return(ret_val);
}
