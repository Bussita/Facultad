#ifndef __QUEUE_H__
#define __QUEUE_H__
#include "glist.h"
typedef struct _GDPList{
    GNode* first;
    GNode* last;
} GDPList;

typedef GDPList* Cola;

Cola cola_crear();

void cola_destruir(Cola cola, FuncionDestructora destroy);

int cola_es_vacia(Cola cola);

void cola_encolar(Cola cola, void* data, FuncionCopia copy);

void* cola_primero(Cola, FuncionCopia);

void cola_desencolar(Cola cola, FuncionDestructora destroy);

void cola_imprimir(Cola cola, FuncionVisitante visit);

#endif