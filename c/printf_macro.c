// C Program to demonstrate the use of macro arguments to
// change the output of printf()
#include <stdio.h>
  
#define printf(x, y) printf(x, 9);

int main()
{
    int i = 10;
    printf("\n i = '%d'\n\n", i);
    return 0;
}
