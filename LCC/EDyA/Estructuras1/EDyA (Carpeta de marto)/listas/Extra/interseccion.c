
#include "../Linked list/slist.h"
#include <stdio.h>

int indice_interseccion(SList lista1, SList lista2);

int main() {

  SList lista1 = slist_crear();

  slist_agregar_inicio(&lista1, 9);
  slist_agregar_inicio(&lista1, 8);
  slist_agregar_inicio(&lista1, 7);
  SNodo* interseccion = lista1;
  slist_agregar_inicio(&lista1, 3);
  slist_agregar_inicio(&lista1, 2);
  slist_agregar_inicio(&lista1, 1);

  SList lista2 = slist_crear();
  slist_agregar_final(&lista2, 5);
  slist_agregar_final(&lista2, 6);
  slist_agregar_final(&lista2, 7);

  lista2->next->next->next = interseccion;


  printf("Indice interseccion: %d\n",indice_interseccion(lista1,lista2));

  return 0;
}


int indice_interseccion(SList lista1, SList lista2) {

  int indice_interseccion = 0;
  int encontrado = 0;

  SNodo* temp1;
  SNodo* temp2;

  for (temp1 = lista1 ; temp1 != NULL && ! encontrado ; temp1 = temp1->next) {

    for (temp2 = lista2 ; temp2 != NULL && ! encontrado ; temp2 = temp2->next)

      if (temp2 == temp1) encontrado = 1;

    // Sumamos solo si no encontramos la interseccion
    if (! encontrado) indice_interseccion++;
  }

  if (! encontrado) return -1;

  return indice_interseccion;
}