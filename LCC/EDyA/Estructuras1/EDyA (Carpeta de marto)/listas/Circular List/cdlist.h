#ifndef __CDLIST_H__
#define __CDLIST_H__

typedef void (*FuncionVisitante) (int dato);

typedef struct _DNodo {

  int dato;
  struct _DNodo* sig;
  struct _DNodo* ant;

} DNodo;

// Solo necesitamos el puntero al primero
typedef DNodo* CDList;


typedef enum {

  DLIST_RECORRIDO_HACIA_ADELANTE,
  DLIST_RECORRIDO_HACIA_ATRAS

} DListOrdenRecorrido;


CDList cdlist_crear();

void cdlist_destruir(CDList lista);

int cdlist_vacia(CDList lista);

void cdlist_agregar(CDList* lista, int dato);

void cdlist_recorrer(CDList lista, FuncionVisitante visit, DListOrdenRecorrido direccion);

int cdlist_longitud(CDList lista);

#endif