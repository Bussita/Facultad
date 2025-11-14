#ifndef __XOR_H__
#define __XOR_H__

#include <stdlib.h>

typedef void (*FuncionRecorrer) (int);

typedef struct _XNodo {

  int dato;
  struct _XNodo *xor;

} XNodo;


typedef struct {
  
  XNodo* primero;
  XNodo* ultimo;

} XList;


typedef enum {

  DERECHA,
  IZQUIERDA

} DireccionRecorrido;



XList xlist_crear();

XList xlist_agregar_inicio(XList lista, int dato);

XList xlist_agregar_final(XList lista, int dato);

int xlist_vacia(XList lista);

void xlist_recorrer(XList lista, FuncionRecorrer funcion, DireccionRecorrido direccion);

void xlist_destruir(XList lista);

#endif