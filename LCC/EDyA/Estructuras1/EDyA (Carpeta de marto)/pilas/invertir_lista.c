#include <stdio.h>
#include <stdlib.h>
#include "pila_gl.h"
#include "../listas/General list/glist_v2.h"


// Ejercicio para invertir una lista usando un stack

GList glist_invertir_stack(GList lista, FuncionCopia c, FuncionDestructora d);


GList glist_invertir_stack(GList lista, FuncionCopia c, FuncionDestructora d) {

  GList lista_invertida = glist_crear();

  Pila pila_inversion = pila_crear();

  // Agregamos los nodos al Stack
  for (GNode* temp = lista.first ; temp != NULL ; temp = temp->next)
    
    pila_inversion = pila_apilar(pila_inversion, temp->data, c);


  // Agregamos a la lista invertida desde el stack
  while (! pila_es_vacia(pila_inversion)) {

    // Tomamos el tope
    void* tope = pila_tope(pila_inversion, c);

    // Lo agregamos a la lista invertida
    lista_invertida = glist_agregar_final(lista_invertida, tope, c);
    free(tope);

    // Lo sacamos del stack
    pila_inversion = pila_desapilar(pila_inversion, d);
  }

  // Destruimos la pila de inversion
  pila_destruir(pila_inversion, d);

  return lista_invertida;
}




