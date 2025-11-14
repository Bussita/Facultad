#ifndef __DLIST_H__
#define __DLIST_H__

typedef void (*FuncionVisitante) (int dato);

typedef struct _DNodo {

  int dato;
  struct _DNodo* sig;
  struct _DNodo* ant;

} DNodo;


typedef struct {

  DNodo* primero;
  DNodo* ultimo;

} DList;


typedef enum {

  DLIST_RECORRIDO_HACIA_ADELANTE,
  DLIST_RECORRIDO_HACIA_ATRAS

} DListOrdenRecorrido;

DList dlist_crear();

void dlist_destruir(DList lista);

int dlist_vacia(DList lista);

void dlist_agregar_final(DList* lista, int dato);

void dlist_agregar_inicio(DList* lista, int dato);

void dlist_recorrer(DList lista, FuncionVisitante visit, DListOrdenRecorrido direccion);

int dlist_longitud(DList lista);

#endif