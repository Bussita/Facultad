#include "glist.h"
#include <assert.h>
#include <stdlib.h>


/**
 * Devuelve una lista vacía.
 */
GList glist_crear() { return NULL; }

/**
 * Destruccion de la lista.
 * destroy es una función que libera el dato almacenado.
 */
void glist_destruir(GList list, FuncionDestructora destroy) {
  GNode* nodo_eliminado;
  
  while (list != NULL) {

    nodo_eliminado = list;
    list = list->next;
    destroy(nodo_eliminado->data);
    free(nodo_eliminado);
  }
}


/**
 * Determina si la lista es vacía.
 */
int glist_vacia(GList list) { return (list == NULL); }


/**
 * Agrega un elemento al inicio de la lista.
 * copy es una función que retorna una copia física del dato.
 */
GList glist_agregar_inicio(GList list, void *data, FuncionCopia copy) {

  GNode* nuevo_nodo = (GNode*) malloc(sizeof(GNode));
  nuevo_nodo->data = copy(data);  
  nuevo_nodo->next = list;
  return nuevo_nodo;
}


GList glist_eliminar_inicio(GList list, FuncionDestructora d) {

  if (list == NULL) return list;

  GNode* nuevo_comienzo = list->next;
  
  // Liberamos el primer nodo
  d(list->data);
  free(list);

  return nuevo_comienzo;
}


/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void glist_recorrer(GList list, FuncionVisitante visit) {
  for (GNode *node = list; node != NULL; node = node->next)
    visit(node->data);
}



GList glist_filtrar(GList lista, FuncionCopia c, Predicado p) {

  GList nueva_lista = glist_crear();

  for (GNode *temp = lista ; temp != NULL ; temp = temp->next) {

    if (p(temp->data))
      nueva_lista = glist_agregar_inicio(nueva_lista, temp->data, c);
  }

  return nueva_lista;
}



GList glist_invertir(GList lista, FuncionCopia c) {

  GList invertida = glist_crear();

  for (GNode* temp = lista ; temp != NULL ; temp = temp->next)
    invertida = glist_agregar_inicio(invertida, temp->data, c);

  return invertida;
}
