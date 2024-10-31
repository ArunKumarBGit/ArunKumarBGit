#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void
print_pattern(const int n)
{
    int i = 0;
    int j = 0;
    int min = 0;
    
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            min = (i > j) ? j : i;
            printf("%d ", n - min + 1);
        }
        for (j = n-1; j >=1; j--) {
            min = (i > j) ? j : i;
            printf("%d ", n - min + 1);
        }
        printf("\n");
    }
    
    for (i = n-1; i >= 1; i--) {
        for (j = 1; j <= n; j++) {
            min = (i > j) ? j : i;
            printf("%d ", n - min + 1);
        }
        for (j = n-1; j >=1; j--) {
            min = (i > j) ? j : i;
            printf("%d ", n - min + 1);
        }
        printf("\n");
    }

}

int main() 
{

    int n = 0;

    printf("\nEnter number to draw pattern: ");
    scanf("%d", &n);
    printf("\n");

  	// Complete the code to print the pattern.
    print_pattern(n);
    printf("\n\n");

    return 0;
}
