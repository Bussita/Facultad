#include "glist.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
/**
 * Devuelve una lista vacía.
 */
GList glist_crear() { return NULL; }

/**
 * Destruccion de la lista.
 * destroy es una función que libera el dato almacenado.
 */
void glist_destruir(GList list, FuncionDestructora destroy) {
  GNode *nodeToDelete;
  while (list != NULL){
    nodeToDelete = list;
    list = list->next;
    destroy(nodeToDelete->data);
      free(nodeToDelete);
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
  GNode *newNode = malloc(sizeof(GNode));
  assert(newNode != NULL);
  newNode->next = list;
  newNode->data = copy(data);
  return newNode;
}

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void glist_recorrer(GList list, FuncionVisitanteG visit) {
  for (GNode *node = list; node != NULL; node = node->next)
    visit(node->data);
}

GList glist_filtrar(GList lista, FuncionCopia copy, Predicado p){
  GList nueva = glist_crear();
  for(GNode* nodo = lista; nodo!=NULL; nodo= nodo->next){
    if(p(nodo->data)){
      nueva = glist_agregar_inicio(nueva, nodo->data, copy);
    }
  }
  return nueva;
}

SGList sglist_crear(){return NULL;}

void sglist_eliminar(SGList lista, FuncionDestructora destroy){
  glist_destruir(lista, destroy);
}

int sglist_vacia(SGList lista){ return (lista == NULL);}

void sglist_recorrer(SGList lista, FuncionVisitanteG visit){
  glist_recorrer(lista, visit);
}

int glist_buscar(GList lista, FuncionComparadora cmp, void* data){
  for(GNode* temp = lista; temp!=NULL; temp = temp->next){
    if(cmp(temp->data,data)==0) return 1;
  }
  return 0;
}

SGList sglist_insertar(SGList lista, FuncionCopia copy, FuncionComparadora compare, void* dato){
  GNode* nuevoNodo = malloc(sizeof(GNode));
  nuevoNodo->data = copy(dato);
  if(sglist_vacia(lista)){
    nuevoNodo->next = NULL;
    return nuevoNodo;
  }
  if(compare(lista->data,dato)==1){
    return glist_agregar_inicio(lista, dato, copy);
  }
  int status = 0;
  GNode* node = lista;
  for(;node->next != NULL && status!=1;node = node->next){
    if(compare(node->next->data, dato)==1){
      nuevoNodo->next = node->next;
      node->next = nuevoNodo;
      status = 1;
    }
  }
  if(node->next==NULL){
    nuevoNodo->next = NULL;
    node->next = nuevoNodo;
  }
  return lista;
}

int sglist_buscar(SGList lista, void* data, FuncionComparadora function){
  for(GNode* node = lista; node!=NULL; node=node->next){
    if(function(data, node->data)==0){
      return 1;
    }
  }
  return 0;
}

SGList sglist_arr(void** arrdata, int longitud, FuncionCopia copy, FuncionComparadora compare){
  SGList lista=sglist_crear();
  for(int i=0; i<longitud; i++){
    lista = sglist_insertar(lista, copy, compare, arrdata[i]);
  }
  return lista;
}