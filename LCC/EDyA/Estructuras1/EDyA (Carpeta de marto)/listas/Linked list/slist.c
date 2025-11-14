#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "slist.h"


// Se realiza instantaneamente
// No depende del tamanio de sus argumentos
SList slist_crear() {
  return NULL;
}

// Tiene que recorrer toda la lista
// Depende del tamanio de sus argumentos
void slist_destruir(SList lista) {

  SNodo* nodo_a_eliminar;

  while(lista != NULL) {
    
    nodo_a_eliminar = lista;
    lista = lista->next;
    free(nodo_a_eliminar);
  }
}

// Se realiza instantaneamente
// No depende del tamanio de sus argumentos
int slist_vacia(SList lista) {
  return lista == NULL;
}

// Debe recorrer toda la lista
// Depende del tamanio de sus argumentos
void slist_agregar_final(SList* lista, int dato) {

  SNodo* nuevo_nodo = malloc(sizeof(SNodo));
  nuevo_nodo->dato = dato;
  nuevo_nodo->next = NULL;

  if (*lista == NULL) {
    *lista = nuevo_nodo;
    return;
  }

  SNodo* temp;

  // Llegamos al final de la lista
  for (temp = *lista ; temp->next != NULL ; temp = temp->next);
  
  temp->next = nuevo_nodo;

  return;
}

// Estamos asignando valores nomas, es instantaneo
// No depende del tamanio de sus argumentos
void slist_agregar_inicio(SList* lista, int dato) {

  SNodo* nuevo_nodo = malloc(sizeof(SNodo));
  nuevo_nodo->dato = dato;

  if (*lista == NULL) {
    nuevo_nodo->next = NULL;
    *lista = nuevo_nodo;
    return;
  }

  nuevo_nodo->next = *lista;
  *lista = nuevo_nodo;

  return;
}


// Debemos recorrer toda la lista y realizar lo que visit tenga que hacer.
// Depende del tamanio de sus argumentos. 
void slist_recorrer(SList lista, FuncionVisitante visit) {

  for (SNodo* nodo = lista ; nodo != NULL ; nodo = nodo->next)
    visit(nodo->dato);
}

// Debe recorrer toda la lista
// Depende del tamanio de sus argumentos. 
int slist_longitud(SList lista) {

  int longitud = 0;

  for (SNodo* nodo = lista ; nodo != NULL ; nodo = nodo->next)
    longitud++;

  return longitud;
}

// Debe recorrer la segunda lista
// Depende del tamanio de su segundo argumentos
SList slist_concatenar(SList lista1, SList lista2) {

  if (! slist_vacia(lista2)) {

    for (SNodo* temp = lista2 ; temp != NULL ; temp = temp->next) 
      slist_agregar_final(&lista1, temp->dato);
  }

  return lista1;  
}

// Debe recorrer hasta encontrar la posicion donde se inserta.
// Depende del tamanio de sus argumentos.
void slist_insertar(SList* lista, int dato) {

  int longitud = slist_longitud(*lista);
  
  srand(time(NULL));
  int pos = rand() % (longitud + 1);

  // Creamos el nuevo nodo
  SNodo* nuevo_nodo = malloc(sizeof(SNodo));
  nuevo_nodo->dato = dato;

  if (pos == 0) {
    nuevo_nodo->next = *lista;
    *lista = nuevo_nodo;
    return;
  }

  SNodo* temp = *lista;

  for (int i = 1 ; i < pos; i++) 
    temp = temp->next;

  nuevo_nodo->next = temp->next;
  temp->next = nuevo_nodo;
}


// Debe recorrer hasta encontrar la posicion que se elimina
// Depende del tamanio de sus argumentos.
void slist_eliminar(SList* lista) {

  int longitud = slist_longitud(*lista);

  srand(time(NULL));
  int pos = rand() % longitud;

  SNodo* nodo_eliminado;

  if (pos == 0) {
 
    nodo_eliminado = *lista;
    *lista = (*lista)->next;
  }

  else {

    SNodo* temp = *lista;

    for (int i = 0 ; i < pos - 1 ; i++)
      temp = temp->next;

    nodo_eliminado = temp->next;
    temp->next = nodo_eliminado->next;
  }

  free(nodo_eliminado);

  return;
}
  // Intentemos renombras las cosas para no tener
  // que hacer excepciones para el primer elemento


// Debe recorrer toda la lista para encontra el dato.
// Depende de el tamanio de sus argumentos.
int slist_contiene(SList lista, int dato) {

  int encontrado = 0; 

  for (SNodo* temp = lista ; temp != NULL && ! encontrado ; temp = temp->next) {

    if (temp->dato == dato)
      encontrado = 1;
  }

  return encontrado;
}


// Debe recorrer toda la lista para encontrar el indice
// Depende del tamanio de sus argumentos.
int slist_indice(SList lista, int dato) {

  int indice = -1;
  int contador = 0; 

  for (SNodo* temp = lista ; temp != NULL && indice == -1 ; temp = temp->next) {

    if (temp->dato == dato)
      indice = contador;
    
    contador++;
  }

  return indice;
}


// Por cada elemento de lista1, debemos recorrer toda la lista2.
// Depende del tamanio de sus argumentos
SList slist_intersecar(SList lista1, SList lista2) {

  SList lista_inteserccion = slist_crear();

  for (SNodo* temp = lista1 ; temp != NULL ; temp = temp->next) {

    if (slist_contiene(lista2, temp->dato))
      slist_agregar_final(&lista_inteserccion, temp->dato);
  } 

  return lista_inteserccion;
}


SList slist_intersecar_custom(SList lista1, SList lista2, FuncionComparacion igualdad) {

  SList lista_intersecar = slist_crear();

  int encontrado;

  for (SNodo* temp = lista1 ; temp != NULL ; temp = temp->next) {

    encontrado = 0;

    for (SNodo* nodo = lista2 ; lista2 != NULL && ! encontrado ; nodo = nodo->next) {

      if (igualdad(temp,nodo)) {
        encontrado = 1;
        slist_agregar_final(&lista_intersecar, nodo->dato);
      }
    }    
  }

  return lista_intersecar;
}
                

// Cambiamos los datos
SList slist_ordenar(SList lista, FuncionComparacion comparar) {

  int buffer;

  for (SNodo* temp1 = lista ; temp1 != NULL ; temp1 = temp1->next) {

    for (SNodo* temp2 = lista ; temp2 != NULL ; temp2 = temp2->next) {
   
      if (comparar(temp1, temp2)) {

        buffer = temp2->dato;
        temp2->dato = temp1->dato;
        temp1->dato = buffer;
      }
    }
  }
  return lista;
}

// TODO: Cambiamos las conexiones entre nodos
SList slist_ordenar_v2(SList lista, FuncionComparacion comparar) {
  return NULL;
}

// TODO: Ir modificando las conexiones entre los nodos
void slist_reverso(SList* lista) {
  return;
}


SList slist_reverso2(SList lista) {

  SList lista_reversa = slist_crear();

  for (SNodo* temp = lista ; temp != NULL ; temp = temp->next) 
    slist_agregar_inicio(&lista_reversa, temp->dato);

  return lista_reversa;
}



SList slist_intercalar(SList lista1, SList lista2) {

  SList lista_intercalada = slist_crear();
  
  SNodo* temp1;
  SNodo* temp2 = lista2;

  for (temp1 = lista1 ; temp1 != NULL ; temp1 = temp1->next) {

    slist_agregar_final(&lista_intercalada, temp1->dato);
    
    if (temp2 != NULL) {
      slist_agregar_final(&lista_intercalada, temp2->dato);
      temp2 = temp2->next;
    }
  }

  // En el caso de que nos hayan quedado elementos en lista2 sin agregar
  for ( ; temp2 != NULL ; temp2 = temp2->next) 
    slist_agregar_final(&lista_intercalada, temp2->dato);

  return lista_intercalada;
}


// En los casos que la longitud sea 1 o 0, el puntero devuelto es NULL
// ya que la segunda mitad tendria largo 0.
SList slist_partir(SList lista) {

  SList segunda_mitad = NULL;

  int longitud = slist_longitud(lista);

  if (longitud <= 1)
    return segunda_mitad; 


  int pos_partir = (longitud - 1) / 2;

  SNodo* temp = lista;

  for (int i = 0 ; i < pos_partir ; i++)
    temp = temp->next;

  segunda_mitad = temp->next;
  temp->next = NULL;

  return segunda_mitad;
}