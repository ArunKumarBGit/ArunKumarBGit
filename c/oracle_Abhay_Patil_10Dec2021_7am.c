#include <stdio.h>

// Objective :: int input[] = {3, '+', 4, '*', 5} 
int calc(int input[], int len) {
    // implement to return the result of the calculation
    
  //int add     = 0;
  //int mul     = 0;
  int i       = 0;
  int total   = 0;
  
  #if 0 // Later optimization
  // Parse operators
  for (i = 1; i < len; i+=2) {
    if (input[i] == '+') {
      add++;
    }
    
    if (input[i] == '*') {
      mul++;
    }
  }
  #endif
  
  // Multiply first
  for (i = 0; i < len; i++) {
    if (input[i] == '*') {
      input[i-1] = input[i-1] * input[i+1];
      
      // Neutralise
      input[i] = '+';
      input[i+1] = 0;
    }
  }
  
  // Add next
  for (i = 0; i < len; i++) {
    if (input[i] == '+') {
      total += input[i-1] + input[i+1];
    }
  }
  
  return(total);
}

int
main (void)
{
  int input[] = {3, '*', 4, '+', 5} ;
  int cnt     = 0;
  
  cnt = sizeof(input)/ sizeof(input[0]);
  
  printf("\nResult = '%d'\n", calc(input, cnt));

  return (0);
}
