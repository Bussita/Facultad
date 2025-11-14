#ifndef __SGLIST_H__
#define __SGLIST_H__

#include "../General list/glist.h"

typedef GList SGList;

typedef int (*FuncionComparadora)(void*, void*);

typedef void* (*FuncionCopia)(void*);

typedef void (*FuncionDestructora)(void*);

typedef void (*FuncionVisitante)(void*);


SGList sglist_crear();

void sglist_destruir(SGList lista, FuncionDestructora destroy);

int sglist_vacia(SGList lista);

void sglist_recorrer(SGList lista, FuncionVisitante visit);

void sglist_insertar(SGList* lista, void* dato, FuncionCopia c, FuncionComparadora comp);

int sglist_buscar(SGList lista, void* dato, FuncionComparadora comp);

SGList sglist_arr(void** datos, int largo, FuncionCopia c, FuncionComparadora comp);

#endif

