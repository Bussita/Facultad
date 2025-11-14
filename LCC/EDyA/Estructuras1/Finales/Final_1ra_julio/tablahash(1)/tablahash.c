#include "tablahash.h"
#include <assert.h>
#include <stdlib.h>
#include "../AVL_REIMLPEMENTACION/avl.h"
#define CARGAMAX 0.15
/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef struct {
  AVL arbol;
  unsigned cargaArbol;
} CasillaHash;

/**
 * Estructura principal que representa la tabla hash.
 */
struct _TablaHash {
  CasillaHash *elems;
  unsigned numElems;
  unsigned capacidad;
  FuncionHash hash;
};

/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
TablaHash tablahash_crear(unsigned capacidad, FuncionCopiadora copia,
                          FuncionComparadora comp, FuncionDestructora destr,
                          FuncionHash hash) {

  // Pedimos memoria para la estructura principal y las casillas.
  TablaHash tabla = malloc(sizeof(struct _TablaHash));
  assert(tabla != NULL);
  tabla->elems = malloc(sizeof(CasillaHash) * capacidad);
  assert(tabla->elems != NULL);
  tabla->numElems = 0;
  tabla->capacidad = capacidad;

  // Inicializamos las casillas con datos nulos.
  for (unsigned idx = 0; idx < capacidad; ++idx) {
    tabla->elems[idx].arbol = avl_crear(comp,copia,destr);
    tabla->elems[idx].cargaArbol = 0;
  }
  return tabla;
}

/**
 * Retorna el numero de elementos de la tabla.
 */
int tablahash_nelems(TablaHash tabla) { return tabla->numElems; }

/**
 * Retorna la capacidad de la tabla.
 */
int tablahash_capacidad(TablaHash tabla) { return tabla->capacidad; }

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash tabla) {

  // Destruir cada uno de los datos.
  for (unsigned idx = 0; idx < tabla->capacidad; ++idx)
    avl_destruir(tabla->elems[idx].arbol);

  // Liberar el arreglo de casillas y la tabla.
  free(tabla->elems);
  free(tabla);
  return;
}

/**
 * Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.
 * IMPORTANTE: La implementacion no maneja colisiones.
 */
void tablahash_insertar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  // Insertar el dato si la casilla estaba libre.
  if(tabla->elems[idx].cargaArbol >= CARGAMAX){
    tablahash_redimensionar(tabla);
  }

  tabla->elems[idx].arbol = avl_insertar(tabla->elems[idx].arbol,dato);
  tabla->elems[idx].cargaArbol = (float)avl_contarelementos(tabla->elems[idx].arbol)/(float)tabla->capacidad;
  tabla->numElems++;
    return;
}

/**
 * Retorna el dato de la tabla que coincida con el dato dado, o NULL si el dato
 * buscado no se encuentra en la tabla.
 */
void *tablahash_buscar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  return avl_buscar(tabla->elems[idx].arbol,dato);
}

/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 */
void tablahash_eliminar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  tabla->elems[idx].arbol = avl_eliminar(tabla->elems[idx].arbol,dato);
  tabla->numElems--;
}

void tablahash_redimensiona_cadaarbol(AVLNodo* arbol, TablaHash nuevaTabla){
  if(arbol == NULL) return;
  tablahash_insertar(nuevaTabla,arbol->data);
  tablahash_redimensiona_cadaarbol(arbol->left,nuevaTabla);
  tablahash_redimensiona_cadaarbol(arbol->right,nuevaTabla);
  return;
}
TablaHash tablahash_redimensionar(TablaHash tabla){
  TablaHash nuevaTabla = tablahash_crear(tabla->capacidad*=2,tabla->elems[0].arbol->copy, tabla->elems[0].arbol->cmp,tabla->elems[0].arbol->dest,tabla->hash);
  for(unsigned idx = 0; idx<tabla->capacidad/2; idx++){
    tablahash_redimensiona_cadaarbol(tabla->elems[idx].arbol->tree,nuevaTabla);
  }
  tablahash_destruir(tabla);
  return nuevaTabla;
}
