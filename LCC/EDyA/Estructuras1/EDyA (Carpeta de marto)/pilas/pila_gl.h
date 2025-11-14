#ifndef __PILA_GL_H__
#define __PILA_GL_H__

#include "../listas/General list/glist_v2.h"

typedef GList Pila;

Pila pila_crear();

void pila_destruir(Pila pila, FuncionDestructora d);

int pila_es_vacia(Pila pila);

void* pila_tope(Pila pila, FuncionCopia c);

Pila pila_apilar(Pila pila, void* dato, FuncionCopia c);

Pila pila_desapilar(Pila pila, FuncionDestructora d);

void pila_imprimir(Pila pila, FuncionVisitante f);

#endif