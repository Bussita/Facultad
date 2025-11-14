#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Fwd_/wtime.h"
#define LARGO 1000000


void copiar_arreglo(int* arreglo_llegada, int* arreglo_salida, int largo) {

  for (int i = 0 ; i < largo; i++)
    arreglo_llegada[i] = arreglo_salida[i];
}


void intercalar(int* arreglo1, int largo1, int* arreglo2, int largo2) {

  // Declaramos arreglos estaticos para copiar la informacion y despues los insertamos
  // en arreglo1. Ya que arreglo1 y arreglo2 son el mismo.

  int copia1[largo1];
  int copia2[largo2];

  copiar_arreglo(copia1, arreglo1, largo1);
  copiar_arreglo(copia2, arreglo2, largo2);

  int indice1 = 0, indice2 = 0;

  for (int i = 0 ; i < largo1 + largo2 ; i++) {

    // Si ya llegamos al final de arreglo1
    if (indice1 == largo1) {

      arreglo1[i] = copia2[indice2];
      indice2 ++;
    }

    // Si llegamos al final de arreglo2
    else if (indice2 == largo2) {

      arreglo1[i] = copia1[indice1];
      indice1 ++;
    }

    // Si el de arreglo1 es menor o igual que el de arreglo2
    else if (copia1[indice1] <= copia2[indice2]) {

      arreglo1[i] = copia1[indice1];
      indice1 ++;
    }

    // Si el de arreglo2 es mayor que el de arreglo1
    else {

      arreglo1[i] = copia2[indice2];
      indice2 ++;
    }

  }
}




void merge_sort(int* arreglo, int largo) {

  // Caso base
  if (largo <= 1) return;

  int medio = largo / 2;

  // Mergeamos cada una de las sublistas
  merge_sort(arreglo, medio);
  merge_sort(arreglo + medio, largo - medio);

  // Intercalamos las sublistas ordenadas
  intercalar(arreglo, medio, arreglo + medio, largo - medio);

  return;
}



int main(void) {

  int arreglo[LARGO];

  srand(time(NULL));

  for (int i = 0 ; i < LARGO ; i++)
    arreglo[i] = rand() % 10000;

  double start = wtime();

  merge_sort(arreglo, LARGO);

  double end = wtime();

  printf("TIEMPO: %f\n",end-start);

  //for (int i = 0 ; i < LARGO; i++) 
  //  printf("%d\n",arreglo[i]);

  return 0;
}