#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

int comparar(int a, int b){
  return a > b;
}
static void imprimir_entero(int dato) {
  printf("%d ", dato);
}

int main(int argc, char *argv[]) {

  SList lista = slist_crear();
  SList lista2 = slist_crear();
  lista = slist_agregar_inicio(lista, 3);
  lista = slist_agregar_inicio(lista, 2);
  lista = slist_agregar_inicio(lista, 1);
  lista = slist_agregar_final(lista, 4);
  lista2 = slist_agregar_inicio(lista2, 3);
  lista2 = slist_agregar_inicio(lista2, 4);
  lista2 = slist_agregar_inicio(lista2, 5);
  lista2 = slist_agregar_final(lista2, 6);
  lista = slist_insertar(lista, 5, 7);
  printf("\n");
  slist_recorrer(lista, imprimir_entero);
  puts("");

  slist_destruir(lista);
  slist_destruir(lista2);
  return 0;
}
