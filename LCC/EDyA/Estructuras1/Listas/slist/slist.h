#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>

typedef void (*FuncionVisitante) (int dato);

typedef struct _SNodo {
  int dato;
  struct _SNodo *sig;
} SNodo;

typedef SNodo *SList;

typedef int (*FuncionComparadora)(void* elemento1, void* elemento2);
/**
 * Devuelve una lista vacía.
 */
SList slist_crear();

/**
 * Destruccion de la lista.
 */
void slist_destruir(SList lista);

/**
 * Determina si la lista es vacía.
 */
int slist_vacia(SList lista);

/**
 * Agrega un elemento al final de la lista.
 */
SList slist_agregar_final(SList lista, int dato);

/**
 * Agrega un elemento al inicio de la lista.
 */
SList slist_agregar_inicio(SList lista, int dato);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void slist_recorrer(SList lista, FuncionVisitante visit);

int slist_longitud(SList lista);

SList slist_concatenar(SList lista, SList lista2);

SList slist_insertar(SList lista, int dato, int pos);

SList slist_eliminar(SList lista,int pos);

int slist_indice(SList lista, int dato);

SList slist_intersecar(SList lista, SList lista2);

SList slist_intersecar_custom(SList lista, SList lista2, FuncionComparadora funcion);

SList slist_ordenar(SList lista, FuncionComparadora funcion);

SList slist_reverso(SList lista);

SList slist_intercalar(SList lista, SList lista2);

SList slist_partir(SList lista);
#endif /* __SLIST_H__ */
