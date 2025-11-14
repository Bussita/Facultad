#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>


typedef struct _SNodo {

  int dato;
  struct _SNodo *next;

} SNodo;


typedef SNodo* SList;

typedef void (*FuncionVisitante) (int dato);

typedef int (*FuncionComparacion) (SNodo* nodo1, SNodo* nodo2);



SList slist_crear();

void slist_destruir(SList lista);

int slist_vacia(SList lista);

void slist_agregar_final(SList* lista, int dato);

void slist_agregar_inicio(SList* lista, int dato);

void slist_recorrer(SList lista, FuncionVisitante visit);

/*
Nos devuelve la longitud de una lista
*/
int slist_longitud(SList lista);

/*
Nos devuelve la concatenacion de dos listas, modificando la priemra
*/
SList slist_concatenar(SList lista1, SList lista2);

/*
Inserta un dato de una posicion arbitraria de la lista
*/
void slist_insertar(SList* lista, int dato);

/*
Borra un dato de una posicion arbitraria de una lista
*/
void slist_eliminar(SList* lista);

/*
Determine si un dato se encuentra o no en la lista
*/
int slist_contiene(SList lista, int dato);

/*
Devuelve la posicion de la primera ocurrencia de un dato si el mismo se 
encuentra en la lista. En caso contrario devuelve -1
*/
int slist_indice(SList lista, int dato);

/*
Devuelve una lista con los elementos comunes de las listas pasadas. Las
listas originales no se modifican.
*/
SList slist_intersecar(SList lista1, SList lista2);

/*
Interseca dos listas, pero la nocion de igualdas se define por la funcion 
pasada por parametro
*/
SList slist_intersecar_custom(SList lista1, SList lista2, FuncionComparacion igualdad);

/*
Ordena una lista de acuerdo al criterio dado por una funcion de compararacion,
la cual es pasada como parametro.
*/
SList slist_ordenar(SList lista, FuncionComparacion comparar);


/*
Lo mismo que la anterior, solo que ahora intercambiamos las conexiones entre
los nodos y nos los datos que contienen.
*/
SList slist_ordenar_v2(SList lista, FuncionComparacion comparar);


/*
Obtiene el reverso de una lista.
*/
void slist_reverso(SList* lista);

/*
Obtiene el reverso de una lista. Otra forma.
*/
SList slist_reverso2(SList lista);

/*
Dadas dos listas, intercale sus elementos en la lista resultante
*/
SList slist_intercalar(SList lista1, SList lista2);

/*
Divide una lista a la mitad. Retorna un puntero al primerelemento de la segunda
mitad. La primera mitad queda apuntada por por el valor pasado.*/
SList slist_partir(SList lista);

#endif /* __SLIST_H__ */