#include "cola_array.h"
#include <stdlib.h>
#include <stdio.h>



Cola cola_crear() {

  Cola nueva_cola = malloc(sizeof(struct _Cola));

  nueva_cola->primero = -1;
  nueva_cola->ultimo = -1;

  return nueva_cola;
}


void cola_destruir(Cola cola) { free(cola); }


int cola_es_vacia(Cola cola) {
  return cola->primero == -1;
}



int cola_inicio(Cola cola) {
  return cola->datos[cola->primero];
}


void cola_encolar(Cola cola, int dato) {

  // Primero veamos si la cola esta llena
  if ((cola->ultimo + 1) % MAX_COLA == cola->primero)
    return;

  // Si es el primer elemento en encolar, seteamos primero y ultimo
  if (cola->primero == -1) {

    cola->primero = 0;
    cola->ultimo = 0;
    cola->datos[cola->ultimo] = dato;
  }

  // En caso contrario, movemos solamente el ultimo
  else {

    cola->ultimo = (cola->ultimo + 1) % MAX_COLA;
    cola->datos[cola->ultimo] = dato;
  }
}

void cola_desencolar(Cola cola) {

  // Chequeamos si esta vacia
  if (cola_es_vacia(cola)) return;

  // Si queda un solo elemento en la cola, la reiniciamos
  if ((cola->primero == cola->ultimo) && cola->primero != -1) {
    
    cola->primero = -1;
    cola->ultimo = -1;
  }

  // Caso contrario, movemos nuevamente el primero
  else 
    cola->primero = (cola->primero + 1) % MAX_COLA;
}


void cola_imprimir(Cola cola) {

  if (cola_es_vacia(cola)) return;

  int i = cola->primero;

  do {

    printf("%d\n",cola->datos[i]);
    i = (i + 1) % MAX_COLA;

  } while (i != (cola->ultimo + 1) % MAX_COLA);
}
