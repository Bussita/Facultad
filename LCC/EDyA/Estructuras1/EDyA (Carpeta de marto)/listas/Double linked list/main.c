#include "dlist.h"
#include <stdio.h>

void imprimir(int dato) { printf("%d \n",dato); }

int main(void) {

  DList lista = dlist_crear();

  dlist_agregar_final(&lista, 3);
  dlist_agregar_final(&lista, 4);
  dlist_agregar_inicio(&lista, 2);
  dlist_agregar_inicio(&lista, 1);

  imprimir(dlist_longitud(lista));
  dlist_recorrer(lista,imprimir,DLIST_RECORRIDO_HACIA_ATRAS);

  dlist_destruir(lista);

  return 0;
}