#include "../Linked list/slist.h"
#include <stdio.h>

// Nos devuelve el indice donde comieza el ciclo
int encontrar_ciclo(SList lista);


int main(void) {

  SList lista = slist_crear();

  slist_agregar_inicio(&lista, 7);
  slist_agregar_inicio(&lista, 6);
  slist_agregar_inicio(&lista, 5);
  slist_agregar_inicio(&lista, 4);
  SNodo* ciclo = lista;
  slist_agregar_inicio(&lista, 3);
  slist_agregar_inicio(&lista, 2);
  slist_agregar_inicio(&lista, 1);
  

  SNodo* temp;
  for (temp = lista ; temp->next != NULL ; temp = temp->next);

  temp->next = ciclo;


  int comienzo_ciclo = encontrar_ciclo(lista);

  printf("El ciclo comienza en %d\n",comienzo_ciclo);
  

    return 0;
}



int encontrar_ciclo(SList lista) {

  // No existe ciclo
  if (slist_vacia(lista)) return 0;

  // Iniciamos nuestros punteros que recorren
  SNodo* lento = lista;
  SNodo* rapido = lista;
  int se_encontraon = 0;


  while (rapido != NULL && ! se_encontraon) {

    // Avanza uno el lento
    lento = lento->next;

    // Avanzamos dos el rapido si el siguiente no es NULL
    if (rapido->next != NULL)
      rapido = rapido->next->next;

    // En caso contrario, llegamos al final
    else rapido = NULL;

    // Vemos si se encontraron
    if (lento == rapido && lento != NULL)
      se_encontraon = 1;
  }

  // No se encontraon, por lo tanto, no existe ciclo
  if (! se_encontraon)
    return -1;

  // Ahora procedemos a encontrar donde comienza el ciclo
  SNodo* lento2 = lista;
  int comienzo_ciclo = 0;

  SNodo* lugar_encuentro = lento;
  int comienzo_ciclo_encontrado = 0;


  while (! comienzo_ciclo_encontrado) {

    do {

      if (lento2 == lento) {
        comienzo_ciclo_encontrado = 1;
      }
      
      lento = lento->next;

    } while (lento != lugar_encuentro && ! comienzo_ciclo_encontrado);



    if (! comienzo_ciclo_encontrado) {

      lento2 = lento2->next;
      comienzo_ciclo++;
    }
  }

  return comienzo_ciclo;
}

