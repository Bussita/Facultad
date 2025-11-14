#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define LARGO 1000000


void insertion_sort(int* arreglo, int largo) {

  int swap;
  int insertado;

  // Considero que el primer elemento esta ordenado
  for (int i = 1 ; i < largo ; i++) {

    insertado = 0;

    for (int j = i - 1 ; j >= 0 && ! insertado ; j--) {

      if (arreglo[j] > arreglo[j + 1]) {

        swap = arreglo[j];
        arreglo[j] = arreglo[j + 1];
        arreglo[j + 1] = swap;
      }

      else insertado = 1;
    }
  }
}


int main(void) {

  int arreglo[LARGO];

  srand(time(NULL));

  for (int i = 0 ; i < LARGO ; i++)
    arreglo[i] = rand() % 10000;

  insertion_sort(arreglo, LARGO);

  //for (int i = 0 ; i < LARGO ; i++) 
  //  printf("%d\n",arreglo[i]);


  return 0;
}