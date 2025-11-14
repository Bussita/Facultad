#include "dlist.h"
#include <stdio.h>
#include <stdlib.h>

DList* dlist_crear(){
    DList* lista=malloc(sizeof(DList));
    lista->primero = NULL;
    lista->ultimo = NULL;
    return lista;
}

DList* dlist_agregar_inicio(DList* lista, int dato){
    DNodo* nuevoNodo = malloc(sizeof(DNodo));
    nuevoNodo->dato = dato;
    nuevoNodo->sig = lista->primero;
    nuevoNodo->ant = NULL;
    if(lista->primero==NULL&&lista->ultimo==NULL){
        lista->primero = nuevoNodo;
        lista->ultimo = nuevoNodo;
        return lista;
    }
    lista->primero->ant = nuevoNodo;
    lista->primero = nuevoNodo;
    return lista;
}

DList* dlist_agregar_final(DList* lista, int dato){
    DNodo* nuevoNodo = malloc(sizeof(DNodo));
    nuevoNodo->dato = dato;
    nuevoNodo->ant = lista->ultimo;
    nuevoNodo->sig = NULL;
    if(lista->primero == NULL && lista->ultimo == NULL){
        lista->primero = nuevoNodo;
        lista->ultimo = nuevoNodo;
        return lista;
    }
    lista->ultimo->sig = nuevoNodo;
    lista->ultimo = nuevoNodo;
    return lista;
}

void dlist_recorrer(DList lista, FuncionVisitante visit, DListOrdenDeRecorrido orden){
    if(orden == DLIST_RECORRIDO_HACIA_ADELANTE){
        for(DNodo* nodo = lista.primero;nodo!=NULL;nodo=nodo->sig){
            visit(nodo->dato);
        }
    }
    if(orden == DLIST_RECORRIDO_HACIA_ATRAS){
        for(DNodo* nodo = lista.ultimo;nodo!=NULL;nodo=nodo->ant){
            visit(nodo->dato);
        }
    }
    return;
}

void dlist_eliminar(DList* lista){
    DNodo* nodeToDelete;
    while(lista->primero!=NULL){
        nodeToDelete = lista->primero;
        lista->primero = lista->primero->sig;
        free(nodeToDelete);
    }
    free(lista);
}