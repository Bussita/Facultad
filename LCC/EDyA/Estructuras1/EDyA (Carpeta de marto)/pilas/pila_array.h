#ifndef __PILA_ARRAY_H__
#define __PILA_ARRAY_H__

#define MAX_PILA 10

struct _Pila {

  int datos[MAX_PILA];
  int ultimo;

};

typedef struct _Pila *Pila;


Pila pila_crear();

void pila_destruir(Pila pila);

int pila_es_vacia(Pila pila);

int pila_tope(Pila pila);

void pila_apilar(Pila pila, int valor);

void pila_desapilar(Pila pila);

void pila_imprimir(Pila pila);

#endif