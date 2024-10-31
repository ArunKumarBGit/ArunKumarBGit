#include <stdio.h>
#include <stdbool.h>

#define SYSERR_SUCCESS          0
#define SYSERR_INVALID_PARAM    -1
#define TRUE                    1
#define FALSE                   0

int
get_dist (int *a_p, int *b_p)
{
    int dist = 0;
    if ((a_p == NULL) || (b_p == NULL)) {
        printf("Invalid parameter\n");
        return(SYSERR_INVALID_PARAM);
    }
    
    dist = (((a_p[0] - b_p[0]) * (a_p[0] - b_p[0])) +
            ((a_p[1] - b_p[1]) * (a_p[1] - b_p[1])));
    
    return(dist);
}


bool 
is_valid_square (int* p1, int* p2, int* p3, int* p4) 
{
    int dist12 = 0;
    int dist13 = 0;
    int dist14 = 0;
    int dist23 = 0;
    int dist34 = 0;
    int dist24 = 0;
    
    if ((p1 == NULL) || (p2 == NULL) || (p3 == NULL) || (p4 == NULL)) {
        printf("Invalid parameter\n");
        return(SYSERR_INVALID_PARAM);
    }
    
    dist12 = get_dist(p1, p2);
    dist13 = get_dist(p1, p3);
    dist14 = get_dist(p1, p4);
    dist23 = get_dist(p2, p3);
    dist34 = get_dist(p3, p4);
    dist24 = get_dist(p2, p4);
    
    if (dist12 == dist13 == dist14 == dist23 == dist34 == dist24) {
        return(FALSE);
    } else if ((dist12 == dist14) && ((2 * dist12) == dist13)) {
        if ((dist23 == dist34) && (dist13 == dist24)) {
            return(TRUE);
        }
    } else if ((dist12 == dist13) && ((2 * dist12) == dist14)) {
        if ((dist24 == dist34) && (dist14 == dist23)) {
            return(TRUE);
        }
    } else if ((dist13 == dist14) && ((2 * dist13) == dist12)) {
        if ((dist23 == dist24) && (dist12 == dist34)) {
            return(TRUE);
        }
    }
    
    return(FALSE);
}

int
main (void)
{
    int p1[] = {1, 0};
    int p2[] = {-1, 0};
    int p3[] = {0, 1};
    int p4[] = {0, -1};

    if (is_valid_square(p1, p2, p3, p4)) {
        printf("\nYes, valid square\n\n");
    } else {
        printf("\nNo, Not a valid square\n\n");
    }

    return(SYSERR_SUCCESS);
}
