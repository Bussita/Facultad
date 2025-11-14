#include "pila_gl.h"


Pila pila_crear() {

  return glist_crear();
}

void pila_destruir(Pila pila, FuncionDestructora d) {

  glist_destruir(pila, d);
}

int pila_es_vacia(Pila pila) {

  return glist_vacia(pila);
}

void* pila_tope(Pila pila, FuncionCopia c) {

  return c(pila.first->data);
}

Pila pila_apilar(Pila pila, void* dato, FuncionCopia c) {

  return glist_agregar_inicio(pila, dato, c);
}

Pila pila_desapilar(Pila pila, FuncionDestructora d) {

  return glist_eliminar_inicio(pila,d);
}

void pila_imprimir(Pila pila, FuncionVisitante f) {

  glist_recorrer(pila, f);
}