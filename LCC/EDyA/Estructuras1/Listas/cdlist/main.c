#include <stdio.h>
#include <stdlib.h>
#include "cdlist.h"

int main(){
    CDList *lista = cdlist_crear();
    lista = cdlist_agregar(lista, 7);
    lista = cdlist_agregar(lista, 8);
    lista = cdlist_agregar(lista, 9);
    //printf("%d\n", lista->primero->ant->dato);
    cdlist_recorrer(lista);
    cdlist_eliminar(lista);
    //printf("%d\n", lista->primero->dato);
    return 0;
}