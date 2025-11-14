#include "priority_queue.h"

#define INITIAL_SIZE 100 // Definimos un tamanio inicial para la PQueue


PQueue pqueue_crear(FuncionComparadora comp, FuncionCopiar copiar,
                                             FuncionDestructora dest) {

  return bheap_crear(INITIAL_SIZE, comp, copiar, dest);
}


int pqueue_vacia(PQueue pqueue) { bheap_es_vacio(pqueue); }


void* pqueue_maximo(PQueue pqueue) { return bheap_maximo(pqueue); }


void pqueue_eliminar(PQueue pqueue) { bheap_eliminar(pqueue); }


void pqueue_insertar(PQueue pqueue, void* dato) { bheap_insertar(pqueue, dato); }