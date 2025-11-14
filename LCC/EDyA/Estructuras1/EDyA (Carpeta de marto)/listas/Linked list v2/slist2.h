#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>


typedef struct _SNodo {

  int dato;
  struct _SNodo *next;

} SNodo;


typedef struct {

  SNodo* primero;
  SNodo* ultimo;

} SList;


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

#endif /* __SLIST2_H__ */