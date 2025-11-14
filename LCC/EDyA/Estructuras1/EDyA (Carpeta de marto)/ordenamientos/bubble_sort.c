#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define LARGO 1000000


void bubble_sort(int* arreglo, int largo) {

  int hiceAlgo = 1;

  int swap;

  while(hiceAlgo) {

    hiceAlgo = 0;

    for (int i = 0 ; i < largo - 1 ; i++) {
      
      if (arreglo[i] > arreglo[i + 1]) {

        swap = arreglo[i];
        arreglo[i] = arreglo[i + 1];
        arreglo[i + 1] = swap;

        hiceAlgo = 1;
      }
    }
  }
}


int main(void) {

  int arreglo[LARGO];

  srand(time(NULL));

  for (int i = 0 ; i < LARGO ; i++)
    arreglo[i] = rand() % 10000;

  bubble_sort(arreglo, LARGO);

  //for (int i = 0 ; i < LARGO ; i++) 
  //  printf("%d\n",arreglo[i]);


  return 0;
}