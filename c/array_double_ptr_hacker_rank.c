#include <stdio.h>
#include <stdlib.h>

/*
Ref: https://www.hackerrank.com/challenges/dynamic-array-in-c/problem?isFullScreen=true

Input:
    5
    5
    1 0 15
    1 0 20
    1 2 78
    2 2 0
    3 0

Output:
    78
    2
 */

/*
 * This stores the total number of books in each shelf.
 */
int* total_number_of_books;

/*
 * This stores the total number of pages in each book of each shelf.
 * The rows represent the shelves and the columns represent the books.
 */
int** total_number_of_pages;
#include <string.h>

int main()
{
    int i = 0;
    
    int total_number_of_shelves;
    scanf("%d", &total_number_of_shelves);
    
    total_number_of_pages = (int **)malloc(total_number_of_shelves * sizeof(int *));
    total_number_of_books = (int *)malloc(total_number_of_shelves * sizeof(int));
    memset(total_number_of_pages, 0, sizeof(total_number_of_shelves * sizeof(int *)));
    memset(total_number_of_books, 0, sizeof(total_number_of_shelves * sizeof(int)));
    
    int total_number_of_queries;
    scanf("%d", &total_number_of_queries);
    
    while (total_number_of_queries--) {
        int type_of_query;
        scanf("%d", &type_of_query);
        
        if (type_of_query == 1) {
            /*
             * Process the query of first type here.
             */
            int x, y;
            scanf("%d %d", &x, &y);
            
           //total_number_of_books[x]++;
            (*(total_number_of_books + x))++;
                                   
            //total_number_of_pages[x] = realloc((void *)total_number_of_pages[x], (total_number_of_books[x] * sizeof(int)));
            //total_number_of_pages[x][total_number_of_books[x] - 1] = y;
            *(total_number_of_pages + x) = realloc((void *)*(total_number_of_pages + x), (*(total_number_of_books + x) * sizeof(int)));
            *((*(total_number_of_pages + x)) + (total_number_of_books[x] - 1)) = y;

        } else if (type_of_query == 2) {
            int x, y;
            scanf("%d %d", &x, &y);
            printf("%d\n", *(*(total_number_of_pages + x) + y));
        } else {
            int x;
            scanf("%d", &x);
            printf("%d\n", *(total_number_of_books + x));
        }
    }

    if (total_number_of_books) {
        free(total_number_of_books);
    }
    
    for (int i = 0; i < total_number_of_shelves; i++) {
        if (*(total_number_of_pages + i)) {
            free(*(total_number_of_pages + i));
        }
    }
    
    if (total_number_of_pages) {
        free(total_number_of_pages);
    }
    
    return 0;
}
