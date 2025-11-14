#include <stdio.h>
#include "xor.h"

void mostrar_entero(int dato) { printf("%d\n",dato); }


int main() {

  XList lista = xlist_crear();

  lista = xlist_agregar_inicio(lista, 1);
  lista = xlist_agregar_inicio(lista, 2);
  lista = xlist_agregar_inicio(lista, 3);
  lista = xlist_agregar_inicio(lista, 4);
  lista = xlist_agregar_inicio(lista, 5);

  xlist_recorrer(lista, mostrar_entero, IZQUIERDA);

  xlist_destruir(lista);

  return 0;
}