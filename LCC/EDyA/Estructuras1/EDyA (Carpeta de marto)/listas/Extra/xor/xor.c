#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "xor.h"

XList xlist_crear() {

  XList nueva_lista;
  nueva_lista.primero = NULL;
  nueva_lista.ultimo = NULL;

  return nueva_lista;
}


XList xlist_agregar_inicio(XList lista, int dato) {

  XNodo* nuevo_nodo = malloc(sizeof(XNodo));
  nuevo_nodo->dato = dato;
  nuevo_nodo->xor = lista.primero;

  if (xlist_vacia(lista)) {

    lista.primero = nuevo_nodo;
    lista.ultimo = nuevo_nodo;
  }

  else { 

    lista.primero->xor = (XNodo*) ((uintptr_t) lista.primero->xor ^(uintptr_t) nuevo_nodo);
    lista.primero = nuevo_nodo;
  }

  return lista;
}



int xlist_vacia(XList lista) { 
  return lista.primero == NULL;
}


void xlist_recorrer(XList lista, FuncionRecorrer funcion, DireccionRecorrido direccion) {

  XNodo* temp;

  if (direccion == DERECHA) {
    
    temp = lista.primero;
    XNodo* anterior = NULL;
    XNodo* actual;

    while (temp != NULL) {

      funcion(temp->dato);

      actual = temp;
      temp = (XNodo*) ((uintptr_t) actual->xor ^ (uintptr_t) anterior);
      anterior = actual;

    }
  }

  if (direccion == IZQUIERDA) {
  
    temp = lista.ultimo;
    XNodo* anterior = NULL;
    XNodo* actual;


    while (temp != NULL) {

      funcion(temp->dato);

      actual = temp;
      temp = (XNodo*) ((uintptr_t) actual->xor ^ (uintptr_t) anterior);
      anterior = actual;
    }

  }

  return;
}


void xlist_destruir(XList lista) {

  XNodo* temp = lista.primero;
  XNodo* anterior = NULL;
  XNodo* actual;

  while (temp != NULL) {


    actual = temp;
    temp = (XNodo*) ((uintptr_t) actual->xor ^ (uintptr_t) anterior);
    anterior = actual;

    free(actual);
  }

}