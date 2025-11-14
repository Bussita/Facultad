#ifndef __DLIST_H__
#define __DLIST_H__

typedef struct _DNodo{
    int dato;
    struct _DNodo* sig;
    struct _DNodo* ant;
} DNodo;

typedef struct _DList{
    DNodo* primero;
    DNodo* ultimo;
} DList;

typedef enum{
    DLIST_RECORRIDO_HACIA_ADELANTE,
    DLIST_RECORRIDO_HACIA_ATRAS
} DListOrdenDeRecorrido;

typedef void (*FuncionVisitante)(int dato);
DList* dlist_crear();

DList* dlist_agregar_inicio(DList* lista, int dato);

DList* dlist_agregar_final(DList* lista, int dato);

void dlist_recorrer(DList lista, FuncionVisitante visit, DListOrdenDeRecorrido orden);

void dlist_eliminar(DList* lista);

#endif