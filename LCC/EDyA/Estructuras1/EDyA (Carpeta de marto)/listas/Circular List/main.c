#include "cdlist.h"
#include <stdio.h>

void imprimir(int dato) { printf("%d \n",dato); }

int main(void) {

  CDList lista = cdlist_crear();

  cdlist_agregar(&lista, 4);
  cdlist_agregar(&lista, 3);
  cdlist_agregar(&lista, 2);
  cdlist_agregar(&lista, 1);


  printf("LARGO: %d\n",cdlist_longitud(lista));

  cdlist_recorrer(lista,imprimir,DLIST_RECORRIDO_HACIA_ADELANTE);

  cdlist_destruir(lista);

  return 0;
}