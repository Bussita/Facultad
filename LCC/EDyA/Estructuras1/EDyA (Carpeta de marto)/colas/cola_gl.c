#include "cola_gl.h"

Cola cola_crear() { return glist_crear(); }

void cola_destruir(Cola cola, FuncionDestructora d) { glist_destruir(cola, d); }

int cola_es_vacia(Cola cola) { return glist_vacia(cola); }

void* cola_inicio(Cola cola, FuncionCopia c) { return c(cola.first->data); }

Cola cola_encolar(Cola cola, void* dato, FuncionCopia c) { return glist_agregar_final(cola, dato, c); }

Cola cola_desencolar(Cola cola, FuncionDestructora d) { return glist_eliminar_inicio(cola, d); }

void cola_imprimir(Cola cola, FuncionVisitante f) { glist_recorrer(cola, f); }