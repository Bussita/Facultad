#include "btree_int.h"
#include <stdio.h>
#include "../../pilas/pila_gl.h" // Stack general
#include "../../colas/cola_gl.h" // Queue general
#include <assert.h>
#include <stdlib.h>



struct _BTNodo {
  int dato;
  struct _BTNodo *left;
  struct _BTNodo *right;
};


/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear() { return NULL; }


/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo) {

  if (nodo != NULL) {

    btree_destruir(nodo->left);
    btree_destruir(nodo->right);
    free(nodo);
  }
}


/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo) { return nodo == NULL; }


/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(int dato, BTree left, BTree right) {
  
  BTree nuevoNodo = malloc(sizeof(struct _BTNodo));

  nuevoNodo->dato = dato;
  nuevoNodo->left = left;
  nuevoNodo->right = right;

  return nuevoNodo;
}


/**
 * Recorrido DFS del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitanteInt visit) {

  // Verificamos si el arbol es vacio
  if (btree_empty(arbol)) return;

  // Ahora vemos el orden rel recorrido

  if (orden == BTREE_RECORRIDO_IN) {

    btree_recorrer(arbol->left, orden, visit);
    visit(arbol->dato);
    btree_recorrer(arbol->right, orden, visit);
  }

  if (orden == BTREE_RECORRIDO_PRE) {

    visit(arbol->dato);
    btree_recorrer(arbol->left, orden, visit);
    btree_recorrer(arbol->right, orden, visit);

  }

  if (orden == BTREE_RECORRIDO_POST) {

    btree_recorrer(arbol->left, orden, visit);
    btree_recorrer(arbol->right, orden, visit);
    visit(arbol->dato);
  }

  return;
}



/**
 * Recorrido DFS de manera iterativa, usando stack
*/
void btree_recorrer_iterativo(BTree arbol, FuncionVisitanteInt visit) {

  if (btree_empty(arbol)) return;

  Pila pila_visita = pila_crear();

  pila_visita = pila_apilar(pila_visita, arbol, id);

  while (! pila_es_vacia(pila_visita)) {

    BTree nodo_actual = pila_tope(pila_visita, id);
    visit(nodo_actual->dato);

    pila_visita = pila_desapilar(pila_visita, skip_destroy);

    if(! btree_empty(nodo_actual->right))
      pila_visita = pila_apilar(pila_visita, nodo_actual->right, id);

    if(! btree_empty(nodo_actual->left))
      pila_visita = pila_apilar(pila_visita, nodo_actual->left, id);
  }

  pila_destruir(pila_visita, skip_destroy);
}



// TODO Pensar que funciones se pueden definir de manera compacta llamando a la
// TODO funcion con un orden, funcion visitante y un dato extra apropiados
/** 
 * Similiar a btree_recorrer solo que el la la funcion visitante se
 * debe aplicar al dato almacenado en el nodo y al dato extra.
*/
void btree_recorrer_extra(BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitanteExtra visit, void* extra) {

  // Verificamos si el arbol es vacio
  if (btree_empty(arbol)) return;

  // Ahora vemos el orden rel recorrido

  if (orden == BTREE_RECORRIDO_IN) {

    btree_recorrer_extra(arbol->left, orden, visit, extra);
    visit(arbol->dato, extra);
    btree_recorrer_extra(arbol->right, orden, visit, extra);
  }

  if (orden == BTREE_RECORRIDO_PRE) {

    visit(arbol->dato, extra);
    btree_recorrer_extra(arbol->left, orden, visit, extra);
    btree_recorrer_extra(arbol->right, orden, visit, extra);

  }

  if (orden == BTREE_RECORRIDO_POST) {

    btree_recorrer_extra(arbol->left, orden, visit, extra);
    btree_recorrer_extra(arbol->right, orden, visit, extra);
    visit(arbol->dato, extra);
  }

  return;
}



/**
 * Recorrido sS, usando la funcion visitante pasada.
*/
void btree_recorrer_bfs(BTree arbol, FuncionVisitanteInt visit) {

  int cantidad_visitados;

  int nivel = 0;

  do {

    cantidad_visitados = btree_recorrer_profundidad_dada(arbol, nivel, visit);
    nivel++;

  } while (cantidad_visitados != 0);
}


/**
 * Aplica la funcion visitante a todos los nodos de cierta altura, y nos devuelve
 * el total de nodos a los que se le aplico la funcion visitante
*/
int btree_recorrer_profundidad_dada(BTree arbol, int profundidad, FuncionVisitanteInt visit) {

  if (btree_empty(arbol)) return 0;

  // Vemos si estamos en la profundidad adecuada
  if (profundidad == 0) { 
    
    visit(arbol->dato);
    return 1;
  }

  // Seguimos recorriendo para abajo
  return btree_recorrer_profundidad_dada(arbol->left, profundidad - 1, visit) +
         btree_recorrer_profundidad_dada(arbol->right, profundidad - 1, visit);
}

/**
 * Recorrido BFS de manera iterativa, usando la funcion visitante pasada
*/
void btree_recorrer_bfs_iterativo(BTree arbol, FuncionVisitanteInt visit) {

  if (btree_empty(arbol)) return;

  Cola cola_visita = cola_crear();

  cola_visita = cola_encolar(cola_visita, arbol, id);

  while (! cola_es_vacia(cola_visita)) {

    BTree nodo_actual = cola_inicio(cola_visita, id);
    visit(nodo_actual->dato);

    if (! btree_empty(nodo_actual->left))
      cola_visita = cola_encolar(cola_visita, nodo_actual->left, id);
    
    if (! btree_empty(nodo_actual->right))
      cola_visita = cola_encolar(cola_visita, nodo_actual->right, id);
    
    cola_visita = cola_desencolar(cola_visita, skip_destroy);
  }

  cola_destruir(cola_visita, skip_destroy);
}



/**
 * Retorna el numero de nodos del arbol
*/
int btree_cantidad_nodos(BTree arbol) {

  if (btree_empty(arbol)) return 0;

  return 1 + btree_cantidad_nodos(arbol->left) + btree_cantidad_nodos(arbol->right);
}


/**
 * Retorna 1 si el numero dado se encuentra en el arbol, 0 en caso contrario
*/
int btree_buscar(BTree arbol, int dato) {

  if (btree_empty(arbol)) return 0;

  if (arbol->dato == dato) return 1;

  if (btree_buscar(arbol->left, dato)) return 1;

  if (btree_buscar(arbol->right, dato)) return 1;

  return 0;
}


/**
 * Retorna un nuevo arbol que se la copia del arbol dado
*/
BTree btree_copiar(BTree arbol) {
  
  if (btree_empty(arbol)) return btree_crear();

  return btree_unir(arbol->dato, btree_copiar(arbol->left), btree_copiar(arbol->right));
}


/**
 * Retorna la altura del arbol
*/
int btree_altura(BTree arbol) {

  if (btree_empty(arbol)) return -1;

  int altura_izquierda = btree_altura(arbol->left); 
  int altura_derecha = btree_altura(arbol->right);

  return altura_derecha > altura_izquierda ? altura_derecha + 1 : altura_izquierda + 1;
}


/**
 * Retorna el numero de nodos que se encuentran a la profundidad dada
*/
int btree_cantidad_nodos_profundidad(BTree arbol, int profundidad) {

  // Vemos si esta vacio
  if (btree_empty(arbol)) return 0;


  if (profundidad == 0) return 1;

  return btree_cantidad_nodos_profundidad(arbol->left, profundidad - 1) +
         btree_cantidad_nodos_profundidad(arbol->right, profundidad - 1);
}


/**
 * Profundidad del nodo que contiene el numero dado y -1 si no se encuentra
*/
int btree_profundidad(BTree arbol, int dato) {

    if (btree_empty(arbol)) return -1;

    if (arbol->dato == dato) return 0;

    int profundidad_izq = btree_profundidad(arbol->left, dato);
    int profundidad_der = btree_profundidad(arbol->right, dato);

    // Vemos si se encuentra en alguna de las ramas
    if (profundidad_izq != -1) return profundidad_izq + 1;

    if (profundidad_der != -1) return profundidad_der + 1;

    // No se encuentra en los subarboles
    return -1;
}


/**
 * Retorna la suma total de los datos del arbol
*/
int btree_sumar(BTree arbol) {

  if (btree_empty(arbol)) return 0;

  return arbol->dato + btree_sumar(arbol->left) + btree_sumar(arbol->right);
}



/**
 * Devuelve la misma direccion que recibio, sin crear copia
 */
void* id(void* nodo) { return nodo; }


/**
 * No destruye nada
 */
void skip_destroy(void* nodo) { return; }
