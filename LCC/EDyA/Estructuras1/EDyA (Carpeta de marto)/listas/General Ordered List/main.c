#include "sglist.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define LARGO 10

void* copiar_entero(void* x);

void mostrar_entero(void* x);

void destruir_entero(void* x);

int comparar_enteros(void* x, void* y);

// PREGUNTAR MANIANA
int main(void) {

  SGList nueva_lista = sglist_crear();

  int** array = malloc(sizeof(int*) * LARGO);


  
  srand(time(NULL));

  for (int i = 0 ; i < LARGO ; i++){
    array[i] = malloc(sizeof(int));
    *(array[i]) = rand() % 100;
  }

  nueva_lista = sglist_arr((void**)array, LARGO, copiar_entero, comparar_enteros);


  sglist_recorrer(nueva_lista,mostrar_entero);

  sglist_destruir(nueva_lista, destruir_entero);


  free(array);

  return 0;
}


void* copiar_entero(void* x) {

  int* p_valor = malloc(sizeof(int));
  *p_valor = *((int*) x);

  return (void*) p_valor;
}

void mostrar_entero(void* x) {
  printf("%d\n",*((int*)x));
}


void destruir_entero(void* x) {
  free(x);
}


int comparar_enteros(void* x, void* y) {

  int a = *((int*)x);
  int b = *((int*)y);

  return a - b; 
}
