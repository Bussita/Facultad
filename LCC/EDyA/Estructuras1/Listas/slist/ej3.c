#include <stdio.h>
#include <stdlib.h>
#include "ej3.h"

SList* slist_crear(){
    SList* lista = malloc(sizeof(SList));
    lista->primero = NULL;
    lista->ultimo = NULL;
    return lista;
}

SList* slist_agregar_inicio(SList* lista,int dato){
    SNodo* nuevoNodo = malloc(sizeof(SNodo));
    nuevoNodo->dato = dato;
    nuevoNodo->sig = lista->primero;
    lista->primero = nuevoNodo;
    return lista;
}

SList* slist_agregar_final(SList* lista, int dato){
    SNodo* nuevoNodo = malloc(sizeof(SNodo));
    nuevoNodo->dato = dato;
    if(lista->ultimo==NULL){
        lista->ultimo = nuevoNodo;
        nuevoNodo->sig = NULL;
        return lista;
    }
    lista->ultimo->sig = nuevoNodo;
    lista->ultimo = nuevoNodo;
    nuevoNodo->sig = NULL;
    return lista;
}
int main(){
    SList* lista = slist_crear();
    lista = slist_agregar_inicio(lista, 5);
    lista = slist_agregar_final(lista, 10);
    printf("%d %d\n",lista->primero->dato,lista->ultimo->dato);
    free(lista->primero);
    free(lista->ultimo);
    free(lista);
    return 0;
}
