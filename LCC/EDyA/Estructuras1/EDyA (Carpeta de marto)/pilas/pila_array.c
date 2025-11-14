#include "pila_array.h"
#include <stdio.h>
#include <stdlib.h>


Pila pila_crear() {

  Pila nueva_pila = malloc(sizeof(struct _Pila));
  nueva_pila->ultimo = -1;

  return nueva_pila;
}

void pila_destruir(Pila pila) { free(pila); }

int pila_es_vacia(Pila pila) { return pila->ultimo == -1; }

int pila_tope(Pila pila) { return pila->datos[pila->ultimo]; }

// Solo apilamos si tenemos espacio
void pila_apilar(Pila pila, int valor) {

  // Si no tenemos espacio
  if (pila->ultimo == MAX_PILA - 1)
    return;

  pila->ultimo ++;
  pila->datos[pila->ultimo] = valor;
}  

void pila_desapilar(Pila pila) {

  // Si la pila esta vacia
  if (pila->ultimo == -1)
    return;

  pila->ultimo --;
}

void pila_imprimir(Pila pila) {

  for (int i = pila->ultimo ; i >= 0 ; i--)
    printf("%d\n",pila->datos[i]);
}
