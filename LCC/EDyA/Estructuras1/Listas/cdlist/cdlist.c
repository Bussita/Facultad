#include <stdio.h>
#include <stdlib.h>
#include "cdlist.h"

CDList* cdlist_crear(){
    CDList *lista = malloc(sizeof(CDList));
    lista->primero = NULL;
    return lista;
}

CDList* cdlist_agregar(CDList *lista,int dato){
    DNodo *nodo = malloc(sizeof(DNodo));
    nodo->dato = dato;
    if (lista->primero == NULL){
        nodo->sig = nodo;
        nodo->ant = nodo;
        lista->primero = nodo;
        return lista;
    }
    nodo->ant = lista->primero->ant;
    lista->primero->ant->sig = nodo;
    nodo->sig = lista->primero;
    lista->primero->ant = nodo;
    lista->primero = nodo;
    return lista;
}

void cdlist_eliminar(CDList* lista){
    DNodo* ultimoNodo = lista->primero->ant;
    while(lista->primero != ultimoNodo){
        DNodo* nodoAEliminar = lista->primero;
        lista->primero = lista->primero->sig;
        free(nodoAEliminar);
    }
    free(ultimoNodo);
    free(lista);
}

void cdlist_recorrer(CDList *lista){
    DNodo *nodo = lista->primero->sig;
    for(;nodo != lista->primero; nodo = nodo->sig){
        printf("%d ", nodo->ant->dato);
    }
    printf("%d", nodo->ant->dato);
}