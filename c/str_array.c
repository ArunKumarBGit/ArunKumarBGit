#include <stdio.h>

int
main (void)
{
    char *arr[] = { "Coding", "never", "fail", "me" };
    char arr_2[][10] = { "Coding", "never", "fail", "me" };
    char a[] = "1010";
    int n = 0;

    n = sizeof(arr) / sizeof(arr[0]);

    printf("\nsizeof(arr) = '%ld', sizeof(arr[0]) = '%ld',\n"
           "sizeof(arr[3]) = '%ld', n = '%d'\n\n",
           sizeof(arr), sizeof(arr[0]), sizeof(arr[3]), n);

    printf("sizeof(arr_2) = '%ld', sizeof(arr_2[0]) = '%ld',\n"
           "sizeof(arr_2[3]) = '%ld', n = '%d'\n\n",
           sizeof(arr_2), sizeof(arr_2[0]), sizeof(arr_2[3]), n);

    printf("sizeof(\"Coding\") = '%ld', sizeof(arr[0]) = '%ld',\n"
           "sizeof(*arr[0]) = '%ld', arr[0] = '%s'\n\n",
           sizeof("Coding"), sizeof(arr[0]), sizeof(&arr[0]), arr[0]);

    printf("\na[0] = '%d' '%c', a[1] = '%d' '%c', sum = '%d'\n\n",
           a[0], a[0], a[1], a[1], (a[0] + a[1] + a[2] + a[3]));

    return(0);
}
