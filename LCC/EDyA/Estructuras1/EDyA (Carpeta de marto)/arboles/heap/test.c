#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_ARRAY 100000

int menor(void* x, void* y) { return *((int*) x) - *((int*) y); }


void destruir_entero(void* dato) { free(dato); }


void* copiar_entero(void* dato) {

  int* copia = malloc(sizeof(int));

  *copia = *((int*) dato);

  return (void*) copia;
}

void mostrar_entero(void* dato) { printf("%d\n", *((int*) dato)); }


void* id(void* dato) { return dato; }


void skip(void* dat) { return; }


int main() {

  BHeap heap = bheap_crear(5, menor, copiar_entero, destruir_entero);

  int* dato = malloc(sizeof(int));
  
  *dato = 10;
  bheap_insertar(heap, dato);

  *dato = 20;
  bheap_insertar(heap, dato);

  *dato = 15;
  bheap_insertar(heap, dato);
  
  *dato =25;
  bheap_insertar(heap, dato);

  *dato = 30;
  bheap_insertar(heap, dato);

  *dato = 16;
  bheap_insertar(heap, dato);

  *dato = 18;
  bheap_insertar(heap, dato);

  *dato = 19;
  bheap_insertar(heap, dato);

  free(dato);

  bheap_recorrer(heap, mostrar_entero);
  bheap_eliminar(heap);

  printf("\n");
  bheap_recorrer(heap, mostrar_entero);


  int arregloo[] = {10,20,15,25,30,16,18,19};

  int** arreglo = malloc(sizeof(int*) * 8);
  for (int i = 0 ; i < 8 ; i++) {
  
    arreglo[i] = malloc(sizeof(int));
    *(arreglo[i]) = arregloo[i]; 
  }
  printf("\n");

  BHeap nuevo = bheap_crear_desde_arr((void**) arreglo, 8, copiar_entero, menor, destruir_entero);
  bheap_recorrer(nuevo, mostrar_entero);

  bheap_destruir(nuevo);


  for (int i = 0 ; i < 8 ; i++) {
    free(arreglo[i]);
  }

  free(arreglo);
  bheap_destruir(heap);

  printf("\n");


  srand(time(NULL));

  int** arreglo2 = malloc(sizeof(int*) * MAX_ARRAY);

  for (int i = 0 ; i < MAX_ARRAY ; i++) {
    
    arreglo2[i] = malloc(sizeof(int));
    *(arreglo2[i]) = rand() % MAX_ARRAY;
  }


  for (int i = 0 ; i < MAX_ARRAY ; i++)
    printf("%d\n",*(arreglo2[i]));

  printf("\n");

  heap_sort((void**) arreglo2, MAX_ARRAY, menor);

  for (int i = 0 ; i < MAX_ARRAY ; i++)
    printf("%d\n",*(arreglo2[i]));

  free(arreglo2);


  return 0;
}


