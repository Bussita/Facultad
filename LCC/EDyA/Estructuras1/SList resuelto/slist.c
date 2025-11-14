#include "slist.h"
#include <stdlib.h>
#include <stdio.h>
SList slist_crear() {
  return NULL;
}

void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar);
  }
}

int slist_vacia(SList lista) {
  return lista == NULL;
}

SList slist_agregar_final(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  if (lista == NULL)
    return nuevoNodo;

  SList nodo = lista;
  for (;nodo->sig != NULL;nodo = nodo->sig);
  /* ahora 'nodo' apunta al ultimo elemento en la lista */

  nodo->sig = nuevoNodo;
  return lista;
}

SList slist_agregar_inicio(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

void slist_recorrer(SList lista, FuncionVisitante visit) {
  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig)
    visit(nodo->dato);
}

int slist_longitud(SList lista){
  int counter=0;
  SList nodo = lista;
  while(nodo!=NULL){
    counter++;
    nodo = nodo->sig;
  }
  return counter;
}

SList slist_concatenar(SList lista, SList lista2){
  SList nodo = lista;
  for(;nodo->sig!=NULL;nodo = nodo->sig);
  nodo->sig = lista2;
  return lista;
}

SList slist_insertar(SList lista, int dato, int posicion){
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  if(lista == NULL){
    nuevoNodo->sig = NULL;
    return nuevoNodo;
  }
  int longitud = slist_longitud(lista);
  SList nodo = lista;
  if(posicion < longitud && posicion >=0){
  for(int i = 0; i<posicion-1; i++){
    nodo = nodo->sig;
  }
  nuevoNodo->sig = nodo->sig;
  nodo->sig = nuevoNodo;
  }else{
    printf("Indice no valido!\n");
    return lista;
  }
  return lista;
}

SList slist_intersecar_custom(SList lista, SList lista2, FuncionComparadora comparar){
  SList nodo = lista;
  SList listaResultado = slist_crear();
  for(;nodo->sig!=NULL;nodo=nodo->sig){
    SList nodo2 = lista2;
    for(;nodo2->sig != NULL; nodo2 = nodo2->sig){
      if(comparar(nodo2->dato,nodo->dato)){
        listaResultado = slist_agregar_final(listaResultado, nodo2->dato);
      }
    }
    if(comparar(nodo2->dato,nodo->dato)){
      listaResultado = slist_agregar_final(listaResultado, nodo2->dato);
    }
  }
  SList aux = lista2;
  for(;aux->sig!=NULL;aux = aux->sig){
    if(comparar(aux->dato,nodo->dato)){
      listaResultado = slist_agregar_final(listaResultado, nodo->dato);
    }
  }
  return listaResultado;
}

SList slist_ordenar(SList lista, FuncionComparadora comparar){
  SList nodo=lista, nodoAux;
  int auxiliar;
  for(;nodo->sig!=NULL;nodo=nodo->sig){
    for(nodoAux=nodo;nodoAux->sig!=NULL; nodoAux = nodoAux->sig){
      if(comparar(nodo->dato,nodoAux->dato)){
        auxiliar = nodo->dato;
        nodo->dato = nodoAux->dato;
        nodoAux->dato = auxiliar;
      }
    }
  }
  int bandera = 1;
  for(nodoAux = lista; bandera;nodoAux = nodoAux->sig){
    if(comparar(nodo->dato,nodoAux->dato)){
      auxiliar = nodo->dato;
      nodo->dato = nodoAux->dato;
      nodoAux->dato = auxiliar;
    }
    if(nodo->sig == nodoAux->sig){
      bandera = 0;
    }
  }
  return lista;
}
