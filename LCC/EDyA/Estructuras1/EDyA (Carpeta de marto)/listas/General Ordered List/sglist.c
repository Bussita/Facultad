#include "sglist.h"
#include <stdlib.h>
#include <stdio.h>

SGList sglist_crear() { return NULL; }

void sglist_destruir(SGList lista, FuncionDestructora destroy) {
  
  GNode* nodo_eliminado;

  while (lista != NULL) {

    nodo_eliminado = lista;
    lista = lista->next;
    destroy(nodo_eliminado->data);
    free(nodo_eliminado);
  }
}



int sglist_vacia(SGList lista) { return lista == NULL; }

void sglist_recorrer(SGList lista, FuncionVisitante visit) {

  for (GNode* temp = lista ; temp != NULL ; temp = temp->next)
    visit(temp->data);
}



void sglist_insertar(SGList* lista, void* dato, FuncionCopia c, FuncionComparadora comp) {

  // Creo el nuevo nodo y copio la data
  GNode* nuevo_nodo = malloc(sizeof(GNode));
  nuevo_nodo->data = c(dato);

  // Si la lista esta vacia
  if (*lista == NULL) {
    
    nuevo_nodo->next = NULL;
    *lista = nuevo_nodo;
    return;
  }

  // Si debemos colocarlo al principio
  if (comp(dato,(*lista)->data) < 0) {

    nuevo_nodo->next = *lista;
    *lista = nuevo_nodo;
    return;
  }

  GNode* temp;

  // Iteramos hasta llegar al ultimo nodo, o cuando encontremos que hay uno que es mayor
  for (temp = *lista; temp->next != NULL && comp(dato, (temp->next)->data) >= 0 ; temp = temp->next );

  nuevo_nodo->next = temp->next;  
  temp->next = nuevo_nodo;

  return;
}

int sglist_buscar(SGList lista, void* dato, FuncionComparadora comp) {

  int encontrado = 0;

  int mayor_encontrado = 0;

  for(GNode* temp = lista ; temp != NULL && ! encontrado && ! mayor_encontrado ; temp = temp->next) {

    if (comp(dato,temp->data) < 0)
      mayor_encontrado = 1;
    
    if (comp(dato, temp->data) == 0)
      encontrado = 1;
  }

  return encontrado;
}




SGList sglist_arr(void** datos, int largo, FuncionCopia c, FuncionComparadora comp) {

  SGList nueva_lista = sglist_crear();

  // Itero sobre el arreglo de datos y los voy agregando a la lista
  for (int i = 0 ; i < largo ; i++) 
    sglist_insertar(&nueva_lista, datos[i], c, comp);

  return nueva_lista;
}
