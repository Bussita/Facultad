#include "cola_gl.h"
#include <stdio.h>
#include <stdlib.h>

void* copiar_entero(void* dato);

void imprimir_entero(void* dato);

void destruir_entero(void* dato);



int main() {

  Cola cola = cola_crear();

  if (cola_es_vacia(cola))
    printf("cola vacia\n");

  int* nuevo_dato = malloc(sizeof(int));
  
  *nuevo_dato = 9;
  cola = cola_encolar(cola,nuevo_dato, copiar_entero);
  
  *nuevo_dato = 10;
  cola = cola_encolar(cola,nuevo_dato, copiar_entero); 
  
  cola = cola_desencolar(cola, destruir_entero);

  void* tope = cola_inicio(cola, copiar_entero);
  printf("%d\n",*((int*) tope));
  free(tope);

  *nuevo_dato = 9;
  cola = cola_encolar(cola,nuevo_dato, copiar_entero);

  *nuevo_dato = 8;
  cola = cola_encolar(cola,nuevo_dato, copiar_entero);

  tope = cola_inicio(cola, copiar_entero);
  printf("%d\n",*((int*) tope));
  free(tope);

  printf("Imprimimos elementos\n");
  cola_imprimir(cola, imprimir_entero);

  cola_destruir(cola, destruir_entero);

  free(nuevo_dato);


  return 0;
} 




void* copiar_entero(void* dato) {

  int* copia = malloc(sizeof(int));
  *copia = *((int*) dato);

  return (void*) copia;
}

void imprimir_entero(void* dato){
  printf("%d\n",*((int*) dato));
}

void destruir_entero(void* dato) {
  free(dato);
}

