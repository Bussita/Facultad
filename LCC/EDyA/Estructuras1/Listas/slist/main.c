#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

static void imprimir_entero(int dato) {
  printf("%d ", dato);
}

int comparar_valor(void* dato1, void* dato2){
  if (*((int*)dato1)==*((int*)dato2)){
    return 0;
  }else if(*((int*)dato1)> *((int*)dato2)){
    return 1;
  } else {
    return -1;
  }
}
int main(int argc, char *argv[]) {

  SList lista = slist_crear();
  lista = slist_agregar_inicio(lista, 3);
  lista = slist_agregar_inicio(lista, 8);
  lista = slist_agregar_inicio(lista, 0);
  lista = slist_agregar_inicio(lista, 15);
  lista = slist_agregar_inicio(lista, 1);
  lista = slist_agregar_inicio(lista, 9);
  lista = slist_agregar_inicio(lista, 2);

  puts("");
  printf("Lista 1: ");
  slist_recorrer(lista, imprimir_entero);
  lista = slist_ordenar(lista, comparar_valor);
  printf("Lista 1: ");
  slist_recorrer(lista, imprimir_entero);

  SList listaNueva = slist_reverso(lista);
  printf("\n Lista reverso: ");
  slist_recorrer(listaNueva, imprimir_entero);
  //listaConcatenada = slist_concatenar(lista,lista2);
  //slist_recorrer(listaConcatenada, imprimir_entero);
  printf("\n");
  slist_destruir(lista);
  slist_destruir(listaNueva);
  return 0;
}
