#include <stdio.h>
#include "heap.h"
#include <stdlib.h>
#include <assert.h>

typedef BHeap PriorityQueue;

static void destruir(void* dato){
    free(dato);
}
int cola_prioridad_es_vacia(PriorityQueue queue){
    return bheap_es_vacio(queue);}

void* cola_prioridad_maximo(PriorityQueue queue){
    assert(!(cola_prioridad_es_vacia(queue)));
    return queue->arr[1];
}

void cola_prioridad_eliminar_maximo(PriorityQueue queue){
    assert(!(cola_prioridad_es_vacia(queue)));
    bheap_eliminar(queue, queue->arr[1], destruir);
}

void cola_prioridad_insertar(PriorityQueue queue, void* dato){
    bheap_insertar(queue, dato);
}