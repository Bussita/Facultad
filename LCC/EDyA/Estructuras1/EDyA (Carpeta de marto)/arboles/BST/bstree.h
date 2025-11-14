#ifndef __BSTREE_ALT_H__
#define __BSTREE_ALT_H__

typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void *, void *);
typedef void (*FuncionDestructora)(void *dato);
typedef void (*FuncionVisitanteExtra)(void *dato, void *extra);

typedef enum {
  BTREE_RECORRIDO_IN,  /** Inorden */
  BTREE_RECORRIDO_PRE, /** Preorden */
  BTREE_RECORRIDO_POST /** Postorden */
} BSTreeRecorrido;

typedef struct _BSTree *BSTree;

/**
 * Retorna un arbol de busqueda binaria vacio.
 * Por unica vez se piden por parametro los punteros a funcion.
 */
BSTree bstee_crear(FuncionCopiadora copiar, FuncionComparadora comp,
                                            FuncionDestructora dest);

/**
 * Destruye el arbol y sus datos.
 */
void bstree_destruir(BSTree arbol);


/**
 * Retorna 1 si el dato se encuentra y 0 en caso contrario.
 */
int bstree_buscar(BSTree arbol, void *dato);


/**
 * Inserta un dato no repetido en el arbol, manteniendo la propiedad del arbol
 * de busqueda binaria.
 */
void bstree_insertar(BSTree arbol, void *dato);


/**
 * Recorrido DSF del arbol
 */
void bstree_recorrer(BSTree arbol, BSTreeRecorrido orden, FuncionVisitanteExtra visit,
                     void *extra);


/**
 * Elimina un dato del arbol, manteniendo la propiedad del arbol de busqueda 
 * binaria.
*/
void bstree_eliminar(BSTree arbol, void* dato);


/**
 * Encuentra el k-esimo menor valor del arbol binario
*/
void* bstree_k_esimo_menor(BSTree arbol, int k);


/**
 * Dado un BT, devuelve 1 si se trata de un BTS, y 0  en 
 * caso contrario.
*/
int bstree_validar(BSTree arbol);


#endif //__BSTREE_ALT_H__