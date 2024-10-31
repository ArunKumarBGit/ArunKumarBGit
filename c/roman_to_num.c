#include <stdio.h>
#include <string.h>

int romanToInt_12Jun2024(char* s) {
    unsigned int len = 0;
    int i = 0;
    int num = 0;
    int lukup_tbl[] = {['I'] = 1, ['V'] = 5, ['X'] = 10,
                       ['L'] = 50, ['C'] = 100,
                       ['D'] = 500, ['M'] = 1000};

    len = strlen(s);

#if 0
    for (i = len-1; i >= 0; i--) {

        if ((s[i] == 'I') || (s[i] == 'V') || (s[i] == 'X') ||
            (s[i] == 'L') || (s[i] == 'C') ||
            (s[i] == 'D') || (s[i] == 'M')) {

            num += lukup_tbl[s[i]];

            if ((i != 0) && (s[i] != 'I')) {
                if ((s[i-1] == 'I') || (s[i-1] == 'X') || (s[i-1] == 'C')) {
                    i--;
                    num -= lukup_tbl[s[i]];
                }
            }
        }
    }
#endif

	for (i = len-1; i >= 0; i--) {
        
        if (s[i] == 'I') {            
            num += lukup_tbl[s[i]];
        }    

        if ((s[i] == 'V') || (s[i] == 'X')) {

            num += lukup_tbl[s[i]];
            
            if (i != 0) {
                if (s[i-1] == 'I') {
                    i--;
                    num -= lukup_tbl[s[i]];
                }
            }
        }

        if ((s[i] == 'L') || (s[i] == 'C')) {

            num += lukup_tbl[s[i]];
            
            if (i != 0) {
                if (s[i-1] == 'X') {
                    i--;
                    num -= lukup_tbl[s[i]];
                }
            }
        }

        if ((s[i] == 'D') || (s[i] == 'M')) {

            num += lukup_tbl[s[i]];
            
            if (i != 0) {
                if (s[i-1] == 'C') {
                    i--;
                    num -= lukup_tbl[s[i]];
                }
            }
        }

    }


    return(num);
}

int 
romanToInt (char * s) 
{
    int len = 0;
    int ptr = 0;
    int num = 0;
    
    len = strlen(s);
    
    while (ptr < len) {
        switch (s[ptr]) {
            case 'M':
                num += 1000;
                ptr++;
                break;
                
            case 'D':
                num += 500;
                ptr++;
                break;
                
            case 'C':
                if (s[ptr+1] == 'D') {
                    num += 400;
                    ptr += 2;
                } else if (s[ptr+1] == 'M') {
                    num += 900;
                    ptr += 2;
                } else {
                    num += 100;
                    ptr++;    
                }
                break;
                
            case 'L':
                num += 50;
                ptr++;
                break;
                
            case 'X':
                if (s[ptr+1] == 'L') {
                    num += 40;
                    ptr += 2;
                } else if (s[ptr+1] == 'C') {
                    num += 90;
                    ptr += 2;
                } else {
                    num += 10;
                    ptr++;
                }
                break;
                
            case 'V':
                num += 5;
                ptr++;
                break;

            case 'I':
                if (s[ptr+1] == 'V') {
                    num += 4;
                    ptr += 2;
                } else if (s[ptr+1] == 'X') {
                    num += 9;
                    ptr += 2;
                } else {
                    num += 1;
                    ptr++;    
                }
                break;
        }
    }
    
    return(num);
}

int
main (void)
{
    char *str = "MCMXCIV";
    printf("Roman = '%s', num = '%d'\n", str, romanToInt(str));
    return(0);
}
