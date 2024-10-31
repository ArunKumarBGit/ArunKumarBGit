#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS     0

int
main (void)
{
    char str_arr[] = "String Array";
    char *str_ptr = "String Pointer";
    char str_lst_arr[][20] = {"Array name 1", "Array name 2", "Ar"};
    //char **str_lst_ptr = {"This resulted in compilation error", "Didn't work"};
    char *str_lst_ptr[] = {"Array name 1", "Array name 2 + some extra"};
    int ret_val = SUCCESS;

    str_ptr = "Assigned new value to String Pointer";
    //str_arr = "Can't assign";
    strcpy(str_arr, "Assigned Arr");

    printf("sizeof(str_arr) = '%ld', sizeof(*str_arr) = '%ld', str_arr = '%s'\n",
            sizeof(str_arr), sizeof(*str_arr), str_arr);
    printf("sizeof(str_ptr) = '%ld', sizeof(*str_ptr) = '%ld', str_ptr = '%s'\n",
            sizeof(str_ptr), sizeof(*str_ptr), str_ptr);

    fprintf(stdout, "\nsizeof(str_lst_arr) = '%ld', "
                    "sizeof(str_lst_arr[0]) = '%ld', "
                    "sizeof(str_lst_arr[2]) = '%ld'\n",
            sizeof(str_lst_arr), sizeof(str_lst_arr[0]), sizeof(str_lst_arr[2]));

    fprintf(stdout, "\nsizeof(str_lst_ptr) = '%ld', "
                    "sizeof(str_lst_ptr[0]) = '%ld', "
                    "sizeof(str_lst_ptr[1]) = '%ld'\n",
            sizeof(str_lst_ptr), sizeof(str_lst_ptr[0]), sizeof(str_lst_ptr[1]));

    str_arr[8] = '_';
    printf("\nModified str_arr = '%s'\n", str_arr);

    //*(str_ptr+8) = '_'; // Run time error, since Read-only string got modified

    //printf("%s", str_arr[0]);     // Character can't use %s
    printf("chr = '%c'\n\n", str_arr[0]);

    return(ret_val);
}
