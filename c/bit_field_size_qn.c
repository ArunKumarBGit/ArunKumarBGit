#include <stdio.h>
 
struct test {
    // Unsigned integer member x
    unsigned int x;
    // Bit-field member y with 33 bits
    long int y : 33;
    // Unsigned integer member z
    unsigned int z;
};
 
int main()
{
    // Declare a variable t of type struct test
    struct test t;
    // Pointer to unsigned int, pointing to member x
    unsigned int* ptr1 = &t.x;
    // Pointer to unsigned int, pointing to member z
    unsigned int* ptr2 = &t.z;
 
    // Print the difference between the two pointers
    printf("%ld\n", (long)ptr2 - (long)ptr1);

    printf("\nsizeof(int) = %ld, sizeof(long int) = %ld\n",
            sizeof(int), sizeof(long int));
 
    return 0;
}
