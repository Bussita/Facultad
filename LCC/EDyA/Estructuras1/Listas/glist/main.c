#include "contacto.h"
#include "glist.h"
#include <stdio.h>
#include <stdlib.h>


int main() {

  SGList lista = sglist_crear();
  Contacto *contactos[6];
  contactos[0] = contacto_crear("Pepe Argento", "3412695452", 61);
  contactos[1] = contacto_crear("Moni Argento", "3412684759", 60);
  contactos[2] = contacto_crear("Coqui Argento", "3415694286", 32);
  contactos[3] = contacto_crear("Paola Argento", "3416259862", 29);
  contactos[4] = contacto_crear("Maria Elena Fuseneco", "3416874594", 59);
  contactos[5] = contacto_crear("Dardo Fuseneco", "3416894526", 64);
  lista = sglist_arr((void**)contactos,6,(FuncionCopia)contacto_copia,(FuncionComparadora)compararEdad);
  for (int i = 0; i < 6; ++i) {
    contacto_destruir(contactos[i]);
  }
  //GList mayoresDeSesenta = glist_filtrar(lista, (FuncionCopia)contacto_copia, (Predicado)mayorASesenta);
  printf("Lista:\n");
  glist_recorrer(lista, (FuncionVisitante)contacto_imprimir);
  //printf("\n Lista mayores a 60: \n");
  //glist_recorrer(mayoresDeSesenta, (FuncionVisitante)contacto_imprimir);
  Contacto* contactoAAgregar = contacto_crear("Raulito", "3131231", 12);
  lista = sglist_insertar(lista,(FuncionCopia)contacto_copia, (FuncionComparadora)compararEdad, contactoAAgregar);
  printf("\nLista:\n");
  glist_recorrer(lista, (FuncionVisitante)contacto_imprimir);
  glist_destruir(lista, (FuncionDestructora)contacto_destruir);
  //glist_destruir(mayoresDeSesenta, (FuncionDestructora)contacto_destruir);
  return 0;
}