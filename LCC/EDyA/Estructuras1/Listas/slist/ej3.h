#ifndef __EJ3_H__
#define __EJ3_H__
typedef struct _SNodo{
    int dato;
    struct _SNodo* sig;
} SNodo;

typedef struct SList{
    SNodo* primero;
    SNodo* ultimo;
} SList;

SList* slist_crear();

SList* slist_agregar_inicio(SList* lista, int dato);

SList* slist_agregar_final(SList* lista, int dato);
#endif