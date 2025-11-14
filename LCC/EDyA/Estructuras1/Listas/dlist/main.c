#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"

void imprimir_entero(int dato){
    printf("%d ",dato);
    return;
}
int main(){
    DList* lista = dlist_crear();
    lista = dlist_agregar_final(lista, 1);
    printf("Ultimo de la lista: %d \n",lista->ultimo->dato);
    lista = dlist_agregar_final(lista, 2);
    printf("Ultimo de la lista: %d \n",lista->ultimo->dato);
    lista = dlist_agregar_final(lista, 3);
    printf("Ultimo de la lista: %d \n",lista->ultimo->dato);
    lista = dlist_agregar_final(lista, 4);
    lista = dlist_agregar_final(lista, 5);
    dlist_recorrer(*lista, imprimir_entero, DLIST_RECORRIDO_HACIA_ADELANTE);
    printf("\n");
    dlist_recorrer(*lista, imprimir_entero, DLIST_RECORRIDO_HACIA_ATRAS);
    dlist_eliminar(lista);
    return 0;
}