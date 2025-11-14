#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Fwd_/wtime.h"
#define LARGO 1000000


void quick_sort(int* arreglo, int largo);

int particionar(int* arreglo, int largo, int pivot);



int main(void) {

  int arreglo[LARGO];

  srand(time(NULL));

  for (int i = 0 ; i < LARGO ; i++)
    arreglo[i] = rand() % 100000;


  double start = wtime();

  quick_sort(arreglo, LARGO);

  double end = wtime();

  printf("TIEMPO: %f\n",end-start);




  //for (int i = 0 ; i < LARGO ; i++) 
  //  printf("%d\n",arreglo[i]);

  return 0;
}


// Elegimos el pivot de manera random
void quick_sort(int* arreglo, int largo) {

  if (largo <= 1) return;

  int indicePivot = rand() % largo;
  int pivot = arreglo[indicePivot];

  // Muevo el pivot al final
  int swap = arreglo[indicePivot];
  arreglo[indicePivot] = arreglo[largo - 1];
  arreglo[largo - 1] = swap;

  // Acomodamos los valores dentro del arreglo respecto a nuetro pivot
  int cantidadMenores = particionar(arreglo, largo - 1, pivot);

  // Posicionamos el pivot en su lugar correcto
  arreglo[largo - 1] = arreglo[cantidadMenores];
  arreglo[cantidadMenores] = pivot;

  // Ordenamos con quick sort los subarreglos particioandos
  quick_sort(arreglo, cantidadMenores);
  quick_sort(arreglo + cantidadMenores + 1 , largo - cantidadMenores - 1);

  return; 
}


// TODO: IMPLEMENTACION: Intercambiar solo cuando no se cumple que no estan ordenados


int particionar(int* arreglo, int largo, int pivot) {

  int cantidadMenores = 0;
  int swap;

  for (int i = 0 ; i < largo ; i++) {

    if (arreglo[i] <= pivot){

      // Intercambiamos los valores
      swap = arreglo[i];
      arreglo[i] = arreglo[cantidadMenores];
      arreglo[cantidadMenores] = swap;

      cantidadMenores++;
    }
  }

  return cantidadMenores;
}

