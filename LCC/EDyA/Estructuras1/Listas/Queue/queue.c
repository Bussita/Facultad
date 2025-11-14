#include <stdio.h>
#include <stdlib.h>
#include "glist.h"
#include "queue.h"

Cola cola_crear(){
    Cola cola = malloc(sizeof(GDPList));
    cola->first = NULL;
    cola->last = NULL;
    return cola;
}

void cola_destruir(Cola cola, FuncionDestructora destroy){
    glist_destruir(cola->first, destroy);
    free(cola);
}

int cola_es_vacia(Cola cola){return (cola->first == NULL);}

void* cola_inicio(Cola cola, FuncionCopia copy){
    void* data = copy(cola->first->data);
    return data;
}

void* cola_primero(Cola cola, FuncionCopia copy){
    return copy(cola->first->data);
}
void cola_encolar(Cola cola, void* data, FuncionCopia copy){
    GNode* nuevoNodo = malloc(sizeof(GNode));
    nuevoNodo->next = NULL;
    nuevoNodo->data = copy(data);
    if(cola->first == NULL && cola->last == NULL){
        cola->first = nuevoNodo;
        cola->last = nuevoNodo;
    }else{
    cola->last->next = nuevoNodo;
    cola->last = nuevoNodo;
    }
}

void cola_desencolar(Cola cola, FuncionDestructora destroy){
    GNode* nodeToDelete = cola->first;
    cola->first = cola->first->next;
    destroy(nodeToDelete->data);
    free(nodeToDelete);
}

void cola_imprimir(Cola cola, FuncionVisitante visit){
    glist_recorrer(cola->first, visit);
}

