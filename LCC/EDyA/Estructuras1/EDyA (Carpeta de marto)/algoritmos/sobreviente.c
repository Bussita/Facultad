#include <stdio.h>
#include <math.h> // Run with -lm

#define MAX_TEST 10000

int survivor(int N) {

  int k = 0;

  while (pow(2,k) <= N) 
    k++;

  return 2 * N - pow(2,k) + 1;
}


int main(void) {

  for (int i = 1 ; i < MAX_TEST ; i++)
    printf("N: %d ---> Survivor: %d",i,survivor(i));


  return 0;
}