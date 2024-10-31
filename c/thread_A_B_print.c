#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

pthread_mutex_t mut_a, mut_b;

void *
print_a()
{
    int ret_val = 0;

    while (1) {
        ret_val = pthread_mutex_lock(&mut_a);
        if (ret_val != 0) {
            printf("Failed to wait for mut_a, ret_val = '%d'\n", ret_val);
            return(NULL);
        }

        printf("A\n");
        sleep(4);

        ret_val = pthread_mutex_unlock(&mut_b);
        if (ret_val != 0) {
            printf("Failed to post for mut_a, ret_val = '%d'\n", ret_val);
            return(NULL);
        }
    }
}


void *
print_b()
{
    int ret_val = 0;

    while (1) {
        ret_val = pthread_mutex_lock(&mut_b);
        if (ret_val != 0) {
            printf("Failed to wait for mut_a, ret_val = '%d'\n", ret_val);
            return(NULL);
        }

        printf("B\n");
        sleep(1);

        ret_val = pthread_mutex_unlock(&mut_a);
        if (ret_val != 0) {
            printf("Failed to post for mut_a, ret_val = '%d'\n", ret_val);
            return(NULL);
        }
    }
}


int
main()
{
    pthread_t t1, t2;
    int ret_val = 0;

    ret_val = pthread_mutex_init(&mut_a, NULL);
    if (ret_val != 0) {
        printf("Failed to create mut_a, ret_val = '%d'\n", ret_val);
        return(ret_val);
    }

    ret_val = pthread_mutex_init(&mut_b, NULL);
    if (ret_val != 0) {
        printf("Failed to create mut_b, ret_val = '%d'\n", ret_val);
        return(ret_val);
    }

    // Lock mut_b, to ensure desired sequence of A B A B...
    ret_val = pthread_mutex_lock(&mut_b);
    if (ret_val != 0) {
        printf("Failed to wait for mut_b, ret_val = '%d'\n", ret_val);
        return(ret_val);
    }

    ret_val = pthread_create(&t1, NULL, &print_a, NULL);
    if (ret_val != 0) {
        printf("Failed to create thread print_a, ret_val = '%d'\n", ret_val);
        return(ret_val);
    }

    ret_val = pthread_create(&t2, NULL, &print_b, NULL);
    if (ret_val != 0) {
        printf("Failed to create thread print_b, ret_val = '%d'\n", ret_val);
        return(ret_val);
    }

    ret_val = pthread_join(t1, NULL);
    if (ret_val != 0) {
        printf("Failed to join thread print_a, ret_val = '%d'\n", ret_val);
        return(ret_val);
    }

    ret_val = pthread_join(t2, NULL);
    if (ret_val != 0) {
        printf("Failed to join thread print_b, ret_val = '%d'\n", ret_val);
        return(ret_val);
    }

    ret_val = pthread_mutex_destroy(&mut_a);
    if (ret_val != 0) {
        printf("Failed to destroy mut_a, ret_val = '%d'\n", ret_val);
        return(ret_val);
    }

    ret_val = pthread_mutex_destroy(&mut_b);
    if (ret_val != 0) {
        printf("Failed to destroy mut_b, ret_val = '%d'\n", ret_val);
        return(ret_val);
    }

    return(0);
}
