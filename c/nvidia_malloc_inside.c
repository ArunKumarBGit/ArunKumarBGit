/*
 * Thread 1:
    while(1) {
        printf("A\n");
    }

 * Thread 2:
    while(1) {
        printf("B\n");
    }

    Expected Output: A B A B ...
    Typical Output: B A A B B A B ...

 * Thread 1:
    sem_a = 1;
    sem_b = 0;

    while(1) {
        wait(&sem_a);       // sem_wait
        printf("A\n");
        signal(&sem_b);     // sem_post
    }

 * Thread 2:
    while(1) {
        wait(&sem_b);
        printf("B\n");
        signal(&sem_a);
    }
 */

#include <stdio.h>
#include <stdlib.h>
int
main ()
{
    // What happens in each of these execution?
    // User space <--> Kernel space switching

    int *p = malloc(4096);

    *p = 4;
    p[1] = 9;

    printf("%d\n", *p);
    printf("%d\n", *(p+1));
}
