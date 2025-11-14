#include "dlist.h"
#include <stdlib.h>
#include <stdio.h>

DList dlist_crear() {

  DList nueva_lista;
  nueva_lista.primero = NULL;
  nueva_lista.ultimo = NULL;

  return nueva_lista;
}


void dlist_destruir(DList lista) {

  DNodo* nodo_eliminado; 
  
  DNodo* temp = lista.primero;

  while (temp != NULL) {

    nodo_eliminado = temp;
    temp = temp->sig;
    free(nodo_eliminado);
  }
}


int dlist_vacia(DList lista) {
  return lista.primero == NULL;
}


void dlist_agregar_final(DList* lista, int dato) {

  DNodo* nuevo_nodo = malloc(sizeof(DNodo));
  nuevo_nodo->dato = dato;

  if (lista->primero == NULL) {

    nuevo_nodo->sig = NULL;
    nuevo_nodo->ant = NULL;
    lista->primero = nuevo_nodo;
    lista->ultimo = nuevo_nodo;
  }

  else {

    nuevo_nodo->sig = NULL;
    nuevo_nodo->ant = lista->ultimo;
    lista->ultimo->sig = nuevo_nodo;
    lista->ultimo = nuevo_nodo;
  }
}

void dlist_agregar_inicio(DList* lista, int dato) {
  
  DNodo* nuevo_nodo = malloc(sizeof(DNodo));
  nuevo_nodo->dato = dato;
  
  if (lista->primero == NULL) {

    nuevo_nodo->sig = NULL;
    nuevo_nodo->ant = NULL;
    lista->primero = nuevo_nodo;
    lista->ultimo = nuevo_nodo;
  }

  else {

    nuevo_nodo->ant = NULL;
    nuevo_nodo->sig = lista->primero;
    lista->primero->ant = nuevo_nodo;
    lista->primero = nuevo_nodo;
  }

}


void dlist_recorrer(DList lista, FuncionVisitante visit, DListOrdenRecorrido direccion) {

  if (direccion == DLIST_RECORRIDO_HACIA_ADELANTE) {

    for (DNodo* temp = lista.primero ; temp != NULL ; temp = temp->sig)
      visit(temp->dato);
  }

  else {

    for (DNodo* temp = lista.ultimo ; temp != NULL ; temp = temp->ant)
      visit(temp->dato);
  }
}


int dlist_longitud(DList lista) {

  int longitud = 0;

  for (DNodo* temp = lista.primero ; temp != NULL ; temp = temp->sig)
    longitud++;
  
  return longitud;
}

