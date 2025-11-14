#include "cdlist.h"
#include <stdlib.h>
#include <stdio.h>

CDList cdlist_crear() {
  return NULL;
}


void cdlist_destruir(CDList lista) {

  if (lista == NULL) return;

  DNodo* nodo_eliminado; 
  DNodo* temp = lista;

  do {

    nodo_eliminado = temp;
    temp = temp->sig;
    free(nodo_eliminado);

  } while (temp != lista);

}


int cdlist_vacia(CDList lista) {
  return lista == NULL;
}


void cdlist_agregar(CDList* lista, int dato) {
  
  DNodo* nuevo_nodo = malloc(sizeof(DNodo));
  nuevo_nodo->dato = dato;
  
  if (*lista == NULL) {

    nuevo_nodo->sig = nuevo_nodo;
    nuevo_nodo->ant = nuevo_nodo;
    *lista = nuevo_nodo;
  }

  else {

    nuevo_nodo->sig = (*lista);
    nuevo_nodo->ant = (*lista)->ant;
    
    (*lista)->ant->sig = nuevo_nodo;
    (*lista)->ant = nuevo_nodo;
    (*lista) = nuevo_nodo;
  }
}


void cdlist_recorrer(CDList lista, FuncionVisitante visit, DListOrdenRecorrido direccion) {

  if (lista == NULL) return;

  DNodo* temp = lista;

  if (direccion == DLIST_RECORRIDO_HACIA_ADELANTE) {

    do {

      visit(temp->dato);
      temp = temp->sig;
      
    } while (temp != lista);

  }

  else {
    
    do {

      visit(temp->dato);
      temp = temp->ant;

    } while (temp != lista);
    
    }
}



int cdlist_longitud(CDList lista) {

  int longitud = 0;

  if (lista == NULL) return longitud;  

  DNodo* temp = lista;

  do {

    longitud++;
    temp = temp->sig;

  } while (temp != lista);

  return longitud;

}

