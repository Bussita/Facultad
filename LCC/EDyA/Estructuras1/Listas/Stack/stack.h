#ifndef __STACK_H__
#define __STACK_H__
#include "../glist/glist.h"

typedef GList Pila;

Pila pila_crear();

void pila_destruir(Pila, FuncionDestructora);

int pila_es_vacia(Pila);

void* pila_tope(Pila, FuncionCopia);

Pila pila_apilar(Pila, void*, FuncionCopia);

Pila pila_desapilar(Pila, FuncionDestructora);

void pila_imprimir(Pila, FuncionVisitanteG);

Pila lista_revertir(GList, FuncionCopia);
#endif