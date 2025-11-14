#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include "../heap/heap.h"

typedef int (*FuncionComparadora) (void*, void*);
typedef void (*FuncionDestructora) (void*);
typedef void* (*FuncionCopiar) (void*);
typedef void (*FuncionVisistante) (void*);


typedef BHeap PQueue;


PQueue pqueue_crear(FuncionComparadora comp, FuncionCopiar copiar,
                                             FuncionDestructora dest);

int pqueue_vacia(PQueue pqueue);

void* pqueue_maximo(PQueue pqueue);

void pqueue_eliminar(PQueue pqueue);

void pqueue_insertar(PQueue pqueue, void* dato);


#endif /* __PRIORITY_QUEUE_H__*/