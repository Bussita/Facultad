#include "glist_v2.h"

#include <assert.h>
#include <stdlib.h>


/**
 * Devuelve una lista vacía.
 */
GList glist_crear() { 

  GList nueva_lista;

  nueva_lista.first = NULL;
  nueva_lista.last = NULL;

  return nueva_lista;
}

/**
 * Destruccion de la lista.
 * destroy es una función que libera el dato almacenado.
 */
void glist_destruir(GList list, FuncionDestructora destroy) {
  GNode* nodo_eliminado;
  
  GNode* temp = list.first;

  while (temp != NULL) {

    nodo_eliminado = temp;
    temp = temp->next;
    destroy(nodo_eliminado->data);
    free(nodo_eliminado);
  }
}


/**
 * Determina si la lista es vacía.
 */
int glist_vacia(GList list) { return (list.first == NULL); }


/**
 * Agrega un elemento al inicio de la lista.
 * copy es una función que retorna una copia física del dato.
 */
GList glist_agregar_inicio(GList list, void *data, FuncionCopia copy) {

  GNode* nuevo_nodo = (GNode*) malloc(sizeof(GNode));
  nuevo_nodo->data = copy(data);

  if (glist_vacia(list)) {

    nuevo_nodo->next = NULL;
    list.first = nuevo_nodo;
    list.last = nuevo_nodo;

  }

  else {

    nuevo_nodo->next = list.first;
    list.first = nuevo_nodo;
  }


  return list;
}


GList glist_eliminar_inicio(GList list, FuncionDestructora d) {

  if (glist_vacia(list)) return list;

  GNode* nuevo_comienzo = list.first->next;
  
  // Liberamos el primer nodo
  d(list.first->data);
  free(list.first);

  list.first = nuevo_comienzo;

  return list;
}



GList glist_agregar_final(GList list, void *data, FuncionCopia copy) {

  GNode* nuevo_nodo = (GNode*) malloc(sizeof(GNode));
  nuevo_nodo->data = copy(data);

  if (glist_vacia(list)) {

    nuevo_nodo->next = NULL;
    list.first = nuevo_nodo;
    list.last = nuevo_nodo;

  }

  else {

    nuevo_nodo->next = NULL;
    list.last->next = nuevo_nodo;
    list.last = nuevo_nodo;
  }

  return list;
}



/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void glist_recorrer(GList list, FuncionVisitante visit) {
  for (GNode *node = list.first; node != NULL; node = node->next)
    visit(node->data);
}



GList glist_filtrar(GList lista, FuncionCopia c, Predicado p) {

  GList nueva_lista = glist_crear();

  for (GNode *temp = lista.first ; temp != NULL ; temp = temp->next) {

    if (p(temp->data))
      nueva_lista = glist_agregar_inicio(nueva_lista, temp->data, c);
  }

  return nueva_lista;
}



GList glist_invertir(GList lista, FuncionCopia c) {

  GList invertida = glist_crear();

  for (GNode* temp = lista.first ; temp != NULL ; temp = temp->next)
    invertida = glist_agregar_inicio(invertida, temp->data, c);

  return invertida;
}
