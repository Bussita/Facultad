#include <stdio.h>
#include "../Linked list/slist.h"



typedef struct {

  int inicio;
  int fin;

} Rango;

void imprimir_entero(int dato) { printf("%d\n", dato); }


SList eliminar_subsecuencia_nula(SList lista, int largo);

int dentro_subsecuencias(Rango* subsecuencias, int cantidad, int indice);

int posicion(int* arreglo, int largo, int dato);

int main() {

  SList lista1 = slist_crear();
  SList lista2 = slist_crear();

  slist_agregar_inicio(&lista1, -8);
  slist_agregar_inicio(&lista1, 8);
  slist_agregar_inicio(&lista1, 9);
  slist_agregar_inicio(&lista1, -12);
  slist_agregar_inicio(&lista1, 4);
  slist_agregar_inicio(&lista1, 8);
  slist_agregar_inicio(&lista1, -6);
  slist_agregar_inicio(&lista1, 6);





  slist_agregar_inicio(&lista2, 25);
  slist_agregar_inicio(&lista2, 20);
  slist_agregar_inicio(&lista2, -18);
  slist_agregar_inicio(&lista2, 10);
  slist_agregar_inicio(&lista2, -19);
  slist_agregar_inicio(&lista2, 10);
  slist_agregar_inicio(&lista2, 9);
  slist_agregar_inicio(&lista2, 8);
  slist_agregar_inicio(&lista2, -10);
  slist_agregar_inicio(&lista2, 6);
  slist_agregar_inicio(&lista2, 4);


  SList lista_limpia = eliminar_subsecuencia_nula(lista1, 8);
  printf("Terminado\n");

  slist_recorrer(lista_limpia, imprimir_entero);


  slist_destruir(lista1);
  slist_destruir(lista2);

  return 0;
}


SList eliminar_subsecuencia_nula(SList lista, int largo) {

  int lista_sumas[largo + 1];
  lista_sumas[0] = 0;
  int indice = 1;


  Rango lista_rangos[largo + 1];
  int cantidad_subsecuencias = 0;

  int coincidencia;

  for (SNodo* temp = lista ; temp != NULL ; temp = temp->next) {

    lista_sumas[indice] = lista_sumas[indice - 1] + temp->dato;
    
    coincidencia = posicion(lista_sumas, indice, lista_sumas[indice]);

    if (coincidencia != -1) {

      lista_rangos[cantidad_subsecuencias].inicio = coincidencia;
      lista_rangos[cantidad_subsecuencias].fin = indice;
      cantidad_subsecuencias++;
    }

    indice++;
  }

  // Ahora creamos la lista con los valores que no pertenecen a la subsecuencia
  SList lista_limpia = slist_crear();

  int indice_lista = 0;

  for (SNodo* temp = lista ; temp != NULL ; temp = temp->next) {

    if (! dentro_subsecuencias(lista_rangos, cantidad_subsecuencias, indice_lista))

      slist_agregar_final(&lista_limpia, temp->dato);

    indice_lista++;
  }



  printf("Sumas\n");

  for (int i = 0 ; i <= largo ; i++)
    printf("%d\n", lista_sumas[i]);


  printf("Tuplas\n");

  for (int i = 0 ; i < cantidad_subsecuencias ; i++)
    printf("(%d,%d)\n", lista_rangos[i].inicio, lista_rangos[i].fin);


  return lista_limpia;
}


int posicion(int* arreglo, int largo, int dato) {

  int posicion = -1;

  for (int i = 0 ; i < largo && posicion == -1 ; i++)

    if (arreglo[i] == dato) posicion = i;

  return posicion;
}



int dentro_subsecuencias(Rango* subsecuencias, int cantidad, int indice) {

  int dentro = 0;

  for (int i = 0 ; i < cantidad && ! dentro; i++) {

    if (subsecuencias[i].inicio <= indice && indice < subsecuencias[i].fin)
      dentro = 1;
  }

  return dentro;
}



