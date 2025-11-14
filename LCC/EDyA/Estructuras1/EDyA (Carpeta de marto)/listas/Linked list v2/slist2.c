#include <stdio.h>
#include <stdlib.h>
#include "slist2.h"

int slist_vacia(SList lista) {

  return lista.primero == NULL;

}


SList slist_crear() {

  SList nueva_lista;
  nueva_lista.primero = NULL;
  nueva_lista.ultimo = NULL;

  return nueva_lista;
}

void slist_agregar_inicio(SList* lista, int dato) {

  SNodo* nuevo_nodo = malloc(sizeof(SNodo));
  nuevo_nodo->dato = dato;

  if (lista->primero == NULL) {

    nuevo_nodo->next = NULL;
    lista->primero = nuevo_nodo;
    lista->ultimo = nuevo_nodo; 
  }

  else {

    nuevo_nodo->next = lista->primero;
    lista->primero = nuevo_nodo;    
  }
}



void slist_agregar_final(SList* lista, int dato) {

  SNodo* nuevo_nodo = malloc(sizeof(SNodo));
  nuevo_nodo->dato = dato;

  if (lista->primero == NULL) {

    nuevo_nodo->next = NULL;
    lista->primero = nuevo_nodo;
    lista->ultimo = nuevo_nodo;
  }

  else {

    lista->ultimo->next = nuevo_nodo;
    lista->ultimo = nuevo_nodo;
  }
}


void slist_recorrer(SList lista, FuncionVisitante visit) {

  for (SNodo* nodo = lista.primero ; nodo != NULL ; nodo = nodo->next)
    visit(nodo->dato);
}


void slist_destruir(SList lista) {

  SNodo* nodo_borrado;
  SNodo* temp = lista.primero;

  while (temp != NULL) {

    nodo_borrado = temp;
    temp = temp->next;
    free(nodo_borrado);
  }
}

int slist_longitud(SList lista) {

  int longitud = 0;

  for (SNodo* nodo = lista.primero ; nodo != NULL ; nodo = nodo->next)
    longitud++;

  return longitud;
}

