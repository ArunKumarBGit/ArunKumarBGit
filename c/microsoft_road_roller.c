// https://app.codility.com

/*
 * Example test: ([2, 4, 2, 6, 7, 1], [0, 5, 3, 2, 1, 5], 2)
 *               ([4, 8, 2, 2, 1, 4], [1, 2, 3, 1, 2, 3], 3)
 *               ([0, 3, 6, 5], [0, 3, 2, 4], 1)
 * 
 * Given to 1D arrays X & Y, giving coordinates of the potholes on the road
 * Also W is given, which is width of the road roller
 * Identify the optimal number of drives needed to fix all the potholes
 * During the drive, the road roller would patch the potholes including the
 * beginning & the ending X-axis coordinates
 * Coordinates in the Y-axis don't make any difference for the number of drives
 */
#define INVALID_PARAM       -1

int solution(int X[], int Y[], int N, int W) {
    // write your code in C99 (gcc 6.2.0)
    int i = 0;
    int j = 0;
    int temp = 0;
    int swapped = 0;
    int fixed_width = -1;
    int min_drives = 0;

    // Parameters validity check
    if ((N <= 0) || (W <= 0)) {
        printf("Error :: Invalid parameter, N = '%d', W = '%d'\n", N, W);
        return(INVALID_PARAM);
    }

    // Sort the array X
    for (i = 0; i < N-1; i++) {
        swapped = 0;
        for (j = 0; j < N-1-i; j++) {
            if (X[j] > X[j+1]) {
                temp = X[j];
                X[j] = X[j+1];
                X[j+1] = temp;
                swapped = 1;
            }
        }
        if (swapped == 0) {
            break;
        }
    }

    // Compute the minimum number of road roller drives
    for (i = 0; i < N; i++) {
        if (fixed_width < X[i]) {
            fixed_width = X[i] + W;
            min_drives++;
        }
    }
    
    return(min_drives);
}

