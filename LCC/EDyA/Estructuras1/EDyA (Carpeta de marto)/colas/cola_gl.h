#ifndef __COLA_GL_H__
#define __COLA_GL_H__

#include "../listas/General list/glist_v2.h"

typedef GList Cola;


Cola cola_crear();

void cola_destruir(Cola cola, FuncionDestructora d);

int cola_es_vacia(Cola cola);

void* cola_inicio(Cola cola, FuncionCopia c);

Cola cola_encolar(Cola cola, void* dato, FuncionCopia c);

Cola cola_desencolar(Cola cola, FuncionDestructora d);

void cola_imprimir(Cola cola, FuncionVisitante f);


#endif