#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define LARGO 1000000


void selection_sort(int* arreglo, int largo) {

  int minima_posicion;
  int swap;

  for (int i = 0 ; i < largo ; i++) {

    minima_posicion = i;

    for (int j = i + 1 ; j < largo ; j++) {

      if (arreglo[j] < arreglo[minima_posicion])

        minima_posicion = j;
    }

    // Swapeamos la posicion actual con el minimo encontrado
    swap = arreglo[i];
    arreglo[i] = arreglo[minima_posicion];
    arreglo[minima_posicion] = swap;
  }

}


int main(void) {

  int arreglo[LARGO];

  srand(time(NULL));

  for (int i = 0 ; i < LARGO ; i++)
    arreglo[i] = rand() % 10000;

  selection_sort(arreglo, LARGO);

  //for (int i = 0 ; i < LARGO ; i++) 
  //  printf("%d\n",arreglo[i]);


  return 0;
}