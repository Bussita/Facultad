#include "bstree.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
/**
 * Estructura del nodo del arbol de busqueda binaria.
 * Tiene un puntero al dato (dato),
 * un puntero al nodo raiz del subarbol izquierdo (izq),
 * y un puntero al nodo raiz del subarbol derecho (der).
 */
typedef struct _BST_Nodo {
  void *dato;
  struct _BST_Nodo *izq, *der;
} BSTNodo;


/**
 * bstee_crear: Retorna un arbol de busqueda binaria vacio
 */
BSTree bstee_crear() { return NULL; }

/**
 * bstree_destruir: Destruye el arbol y sus datos
 */
void bstree_destruir(BSTree raiz, FuncionDestructora destr) {
  if (raiz != NULL) {
    bstree_destruir(raiz->izq, destr);
    bstree_destruir(raiz->der, destr);
    destr(raiz->dato);
    free(raiz);
  }
};

/**
 * bstree_buscar: Retorna 1 si el dato se encuentra y 0 en caso
 * contrario
 */
int bstree_buscar(BSTree raiz, void *dato, FuncionComparadora comp) {
  if (raiz == NULL)
    return 0;
  else if (comp(dato, raiz->dato) == 0) // raiz->dato == dato
    return 1;
  else if (comp(dato, raiz->dato) < 0) // dato < raiz->dato
    return bstree_buscar(raiz->izq, dato, comp);
  else // raiz->dato < dato
    return bstree_buscar(raiz->der, dato, comp);
}

/**
 * bstree_insertar: Inserta un dato no repetido en el arbol, manteniendo la
 * propiedad del arbol de busqueda binaria
 */
BSTree bstree_insertar(BSTree raiz, void *dato, FuncionCopiadora copia,
                       FuncionComparadora comp) {
  if (raiz == NULL) { // insertar el dato en un nuevo nodo
    struct _BST_Nodo *nuevoNodo = malloc(sizeof(struct _BST_Nodo));
    assert(nuevoNodo != NULL);
    nuevoNodo->dato = copia(dato);
    nuevoNodo->izq = nuevoNodo->der = NULL;
    return nuevoNodo;
  } else if (comp(dato, raiz->dato) < 0) // dato < raiz->dato
    raiz->izq = bstree_insertar(raiz->izq, dato, copia, comp);
  else if (comp(dato, raiz->dato) > 0) // raiz->dato < dato
    raiz->der = bstree_insertar(raiz->der, dato, copia, comp);
  // si el dato ya se encontraba, no es insertado
  return raiz;
}

/**
 * bstree_recorrer: Recorrido DSF del arbol
 */
void bstree_recorrer(BSTree raiz, BSTreeRecorrido orden,
                     FuncionVisitanteExtra visita, void *extra) {
  if (raiz != NULL) {
    if (orden == BTREE_RECORRIDO_PRE)
      visita(raiz->dato, extra);
    bstree_recorrer(raiz->izq, orden, visita, extra);
    if (orden == BTREE_RECORRIDO_IN)
      visita(raiz->dato, extra);
    bstree_recorrer(raiz->der, orden, visita, extra);
    if (orden == BTREE_RECORRIDO_POST)
      visita(raiz->dato, extra);
  }
}

BSTree bstree_eliminar(BSTree arbol, void* dato, FuncionComparadora cmp, FuncionDestructora destroy){
  if(cmp(arbol->dato, dato) == 0){
    BSTNodo* nodoRemplazo;
    if(arbol->der == NULL && arbol->izq == NULL){
      nodoRemplazo = NULL;
    }
    if(arbol->izq == NULL && arbol->der != NULL){
      nodoRemplazo = arbol->der;
    }
    if(arbol->der == NULL && arbol->izq != NULL){
      nodoRemplazo = arbol->izq;
    }
    if(arbol->der != NULL && arbol->izq != NULL){
      BSTNodo* temporal = arbol->izq, *padreNodoRemplazo;
      if(temporal->der == NULL){
        nodoRemplazo = temporal;
        nodoRemplazo->der = arbol->der;
        destroy(arbol->dato);
        free(arbol);
        return nodoRemplazo;
        }
      while(temporal->der->der!=NULL){
        temporal = temporal->der;
      }
      padreNodoRemplazo = temporal;
      nodoRemplazo = temporal->der;
      nodoRemplazo->der = arbol->der;
      if(nodoRemplazo->izq != NULL){
        padreNodoRemplazo->der = nodoRemplazo->izq;
      }
      nodoRemplazo->izq = arbol->izq;
    }
    destroy(arbol->dato);
    free(arbol);
    return nodoRemplazo;
  }
  if(cmp(arbol->dato,dato) < 0){
  arbol->der = bstree_eliminar(arbol->der, dato, cmp, destroy);
  }
  if(cmp(arbol->dato,dato) > 0){
  arbol->izq = bstree_eliminar(arbol->izq, dato, cmp, destroy);
  }
  return arbol;
}
void* devuelvoSoloelK(BSTree arbol, int* k){
  if(arbol == NULL){ return NULL;}
  void* dato = devuelvoSoloelK(arbol->izq,k);
  if(dato!=NULL){
    return dato;
  }
  if(*k == 0){
    return arbol->dato;
  }
  *k = *k -1;
  return devuelvoSoloelK(arbol->der, k);
  }
void* bstree_k_esimo_menor(BSTree tree, int k){
  return devuelvoSoloelK(tree, &k);
}