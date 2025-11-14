#ifndef __BT_INT_H__
#define __BT_INT_H__

typedef void (*FuncionVisitanteInt)(int dato);
typedef void (*FuncionVisitanteExtra) (int dato, void* extra);


typedef enum {
  BTREE_RECORRIDO_IN,
  BTREE_RECORRIDO_PRE,
  BTREE_RECORRIDO_POST
} BTreeOrdenDeRecorrido;


typedef struct _BTNodo *BTree;


/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear();

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo);

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo);

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(int dato, BTree left, BTree right);

/**
 * Recorrido DFS, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitanteInt visit);


/**
 * Recorrido DFS, pero hecho de forma iterativa.
 */
void btree_recorrer_iterativo(BTree arbol, FuncionVisitanteInt visit);


/**
 * Similiar a btree_recorrer solo que el la la funcion visitante se
 * debe aplicar al dato almacenado en el nodo y al dato extra.
*/
void btree_recorrer_extra(BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitanteExtra visit, void* extra);


/**
 * Recorrido BFS, usando la funcion visitante pasada.
*/
void btree_recorrer_bfs(BTree arbol, FuncionVisitanteInt visit);


/**
 * Aplica la funcion visitante a todos los nodos de cierta altura, y nos devuelve
 * el total de nodos a los que se le aplico la funcion visitante
*/
int btree_recorrer_profundidad_dada(BTree arbol, int profundidad, FuncionVisitanteInt visit);


/**
 * Recorrido BFS de manera iterativa, usando la funcion visitante pasada
*/
void btree_recorrer_bfs_iterativo(BTree arbol, FuncionVisitanteInt visit);


/**
 * Retorna el numero de nodos del arbol
*/
int btree_cantidad_nodos(BTree arbol);


/**
 * Retorna 1 si el numero dado se encuentra en el arbol, 0 en caso contrario
*/
int btree_buscar(BTree arbol, int dato);


/**
 * Retorna un nuevo arbol que se la copia del arbol dado
*/
BTree btree_copiar(BTree arbol);


/**
 * Retorna la altura del arbol
*/
int btree_altura(BTree arbol);



/**
 * Retorna el numero de nodos que se encuentran a la profundidad dada
*/
int btree_cantidad_nodos_profundidad(BTree arbol, int profundidad);


/**
 * Profundidad del nodo que contiene el numero dado y -1 si no se encuentra
*/
int btree_profundidad(BTree arbol, int dato);


/**
 * Retorna la suma total de los datos del arbol
*/
int btree_sumar(BTree arbol);


/**
 * Devuelve la misma direccion que recibio, sin crear copia
 */
void* id(void* nodo);


/**
 * No destruye nada
 */
void skip_destroy(void* nodo);


#endif /* __BTREE_H__ */
