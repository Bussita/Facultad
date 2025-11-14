#include <stdio.h>
#include <stdlib.h>
#include "../glist/glist.h"
#include "stack.h"

Pila pila_crear(){return glist_crear();}

void pila_destruir(Pila pila, FuncionDestructora destroy){
    glist_destruir(pila, destroy);
}

int pila_es_vacia(Pila pila){
    return glist_vacia(pila);
}

void* pila_tope(Pila pila, FuncionCopia copy){
    return copy(pila->data);
}

Pila pila_apilar(Pila pila, void* data, FuncionCopia copy){
    return glist_agregar_inicio(pila, data, copy);
}

Pila pila_desapilar(Pila pila, FuncionDestructora destroy){
    GNode* node;
    for(node = pila; node->next!=NULL; node=node->next);
    destroy(node->data);
    free(node);
    return pila;
}

void pila_imprimir(Pila pila, FuncionVisitanteG visit){
    glist_recorrer(pila, visit);
}

Pila lista_revertir(GList lista, FuncionCopia copy){
    Pila pila = glist_crear();
    for(GNode* node = lista; node!=NULL; node = node->next){
        pila = pila_apilar(pila, node->data, copy);
    }
    return pila;
}