#ifndef __COLA_ARRAY_H__
#define __COLA_ARRAY_H__

#define MAX_COLA 5

struct _Cola {

  int datos[MAX_COLA];
  int primero;
  int ultimo;

};

typedef struct _Cola* Cola;

Cola cola_crear();

void cola_destruir(Cola cola);

int cola_es_vacia(Cola cola);

int cola_inicio(Cola cola);

void cola_encolar(Cola cola, int dato);

void cola_desencolar(Cola cola);

void cola_imprimir(Cola cola);


#endif