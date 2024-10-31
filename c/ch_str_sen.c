#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int 
main(void) 
{
    char ch;
    char s[100];
    char sen[100];
    
    scanf("%c", &ch);
    scanf("%s", s);
    getchar();
    scanf("%[^\n]", sen); // Read a sentence, including spaces
    
    printf("%c\n", ch);
    printf("%s\n", s);
    printf("%s\n", sen);

    return 0;
}
