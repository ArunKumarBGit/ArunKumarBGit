#include <stdio.h>

// https://leetcode.com/problems/can-place-flowers/submissions/

int 
canPlaceFlowers (int* flowerbed, int sz, int n)
{
    int sum = 0;
    int cnt = 0;
    int i = 0;
    
    while (i < sz) {
        printf("\nDBG :: i = '%d', cnt = '%d', n = '%d'", i, cnt, n);
        if (cnt >= n) {
            return(1);
        }
        
        if (flowerbed[i] == 1) {
            i += 2;
        } else if ((i > 0) && (i+1 < sz)) {
            sum = flowerbed[i-1] + flowerbed[i] + flowerbed[i+1];
            if (sum == 0) {
                cnt++;
                i += 2;
            } else {
                i++;
            }
        } else if (i+1 < sz) {
            sum = flowerbed[i] + flowerbed[i+1];
            if (sum == 0) {
                cnt++;
                i += 2;
            } else {
                i++;
            }
        } else if (i > 0) {
            sum = flowerbed[i-1] + flowerbed[i];
            if (sum == 0) {
                cnt++;
                i += 2;
            } else {
                i++;
            }
        } else {
            cnt++;
            i++;
        }
    }

    if (cnt >= n) {
        return(1);
    }
    
    return(0);
}

int
main (void)
{
    int flowerbed[] = {1, 0, 0, 0, 1, 0, 0};
    int sz = sizeof(flowerbed) / sizeof(flowerbed[0]);
    int n = 2;

    printf("\n\nPossibility of planting '%d' plants is '%d'\n\n",
           n, canPlaceFlowers(flowerbed, sz, n));
    return(0);
}
