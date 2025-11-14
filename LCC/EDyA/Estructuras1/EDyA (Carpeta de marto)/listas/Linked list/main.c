#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "slist.h"



static void imprimir_entero(int dato) {
  printf("%d\n",dato);
}


int main(void) {

  SList lista = slist_crear();

  slist_insertar(&lista, 1);
  slist_insertar(&lista, -5);
  slist_insertar(&lista, 10);
  slist_insertar(&lista, 2);


  slist_recorrer(lista, imprimir_entero);
  
  slist_destruir(lista);

  return 0;
}