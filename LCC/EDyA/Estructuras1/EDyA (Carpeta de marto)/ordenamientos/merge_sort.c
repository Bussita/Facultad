#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Fwd_/wtime.h"
#define LARGO 1000000


int* subarreglo(int* arreglo, int inicio, int final) {

  int* nuevo_arreglo = malloc(sizeof(int) * (final - inicio));

  for (int i = 0 ; i < final - inicio ; i++)
    nuevo_arreglo[i] = arreglo[i + inicio];

  return nuevo_arreglo;
}


int* intercalar(int* arreglo1, int largo1, int* arreglo2, int largo2) {

  int* arreglo_intercalado = malloc(sizeof(int) * (largo1 + largo2));

  int indice1 = 0, indice2 = 0;

  for (int i = 0 ; i < largo1 + largo2 ; i++) {

    // Si ya llegamos al final de arreglo1
    if (indice1 == largo1) {

      arreglo_intercalado[i] = arreglo2[indice2];
      indice2 ++;
    }

    // Si llegamos al final de arreglo2
    else if (indice2 == largo2) {

      arreglo_intercalado[i] = arreglo1[indice1];
      indice1 ++;
    }

    // Si el de arreglo1 es menor o igual que el de arreglo2
    else if (arreglo1[indice1] <= arreglo2[indice2]) {

      arreglo_intercalado[i] = arreglo1[indice1];
      indice1 ++;
    }

    // Si el de arreglo2 es mayor que el de arreglo1
    else {

      arreglo_intercalado[i] = arreglo2[indice2];
      indice2 ++;
    }

  }

  return arreglo_intercalado;
}




int* merge_sort(int* arreglo, int largo) {

  // Caso base
  if (largo <= 1) return arreglo;

  int medio = largo / 2;

  // Construimos los subarreglos
  int* mitad1 = subarreglo(arreglo,0,medio);
  int* mitad2 = subarreglo(arreglo,medio,largo);
  free(arreglo);

  // Mergeamos los subarreglos
  mitad1 = merge_sort(mitad1, medio);
  mitad2 = merge_sort(mitad2, largo - medio);

  // Intercalamos las sublistas ordenadas
  int* intercalado = intercalar(mitad1, medio, mitad2, largo - medio);

  free(mitad1);
  free(mitad2);

  return intercalado;
}



int main(void) {

  int* arreglo = malloc(sizeof(int) * LARGO);

  srand(time(NULL));

  for (int i = 0 ; i < LARGO ; i++)
    arreglo[i] = rand() % 10000;


  double start = wtime();

  int* ordenado = merge_sort(arreglo, LARGO);

  double end = wtime();

  printf("TIEMPO: %f\n",end-start);

  //for (int i = 0 ; i < LARGO; i++) 
  //  printf("%d\n",ordenado[i]);

  free(ordenado);

  return 0;
}