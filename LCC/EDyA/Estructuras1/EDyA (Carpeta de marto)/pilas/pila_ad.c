#include "pila_ad.h"
#include <stdlib.h>
#include <stdio.h>


Pila pila_crear(int capacidad) {

  Pila nueva_pila = malloc(sizeof(struct _Pila));

  nueva_pila->ultimo = -1;
  nueva_pila->arr = arreglo_enteros_crear(capacidad);

  return nueva_pila;
}


void pila_destruir(Pila pila) {

  arreglo_enteros_destruir(pila->arr);
  free(pila);
}


int pila_es_vacia(Pila pila) {

  return pila->ultimo == -1;
}


int pila_tope(Pila pila) {

  return arreglo_enteros_leer(pila->arr, pila->ultimo);
}

void pila_apilar(Pila pila, int valor) {

  int capacidad = arreglo_enteros_capacidad(pila->arr);

  // Agrego capacidad si no tengo
  if (capacidad == pila->ultimo + 1) 
    arreglo_enteros_ajustar(pila->arr, capacidad * 2);

  pila->ultimo++;
  arreglo_enteros_escribir(pila->arr, pila->ultimo, valor);
}


void pila_desapilar(Pila pila) {

  if (pila->ultimo != -1) pila->ultimo--;
}

void pila_imprimir(Pila pila) {

  // Imprimimos desde el tope de la pila hasta el fondo
  for (int i = pila->ultimo ; i >= 0 ; i--)
    printf("%d\n", arreglo_enteros_leer(pila->arr, i));
}