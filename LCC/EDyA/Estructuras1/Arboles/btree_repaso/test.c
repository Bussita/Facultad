#include "btree.h"
#include <stdio.h>
#include <stdlib.h>

int* noCopia(int* dato){return dato;}

int comparacion(int* a, int* b){
    if(*a == *b) return 0;
    if(*a < *b) return -1;
    return 1;
}

static void imprimirEntero(int* x){
    printf("%d ",*x);
}

static void destr(void* data){ free(data);}
static void noDestr(void* data){return;}
int main(){
    int* a = malloc(sizeof(int));
    *a = 5;
    int* b = malloc(sizeof(int));
    *b = 10;
    int* c = malloc(sizeof(int));
    *c = 15;
    int* e = malloc(sizeof(int));
    *e = 25;
    BTree ii = btree_agregar_raiz(a,(FuncionCopia) noCopia,btree_crear(),btree_crear());
    BTree i = btree_agregar_raiz(b,(FuncionCopia) noCopia,ii,btree_crear());
    BTree d = btree_agregar_raiz(c,(FuncionCopia) noCopia,btree_crear(),btree_crear());
    BTree raiz = btree_agregar_raiz(e,(FuncionCopia) noCopia,i,d);
    btree_recorrer(raiz, BTREE_RECORRIDO_IN,(FuncionVisitante)imprimirEntero);
    printf("\nCantidad de nodos del arbol: %d\n",btree_nnodos(raiz));
    int datoABuscar = 10;
    if(btree_buscar(raiz, &datoABuscar,(FuncionComparadora)comparacion)){
        printf("El dato %d se encuentra en el arbol.\n",datoABuscar);
    }else{
        printf("El dato %d NO se encuentra en el arbol.\n",datoABuscar);
    }
    BTree arbolCopia = btree_copiar(raiz, (FuncionCopia) noCopia);
    btree_recorrer(arbolCopia, BTREE_RECORRIDO_IN, (FuncionVisitante) imprimirEntero);
    printf("\nLa altura del arbol es %d\n",btree_altura(raiz));
    int profundidad = 1;
    printf("Numero de nodos a profundidad %d son %d\n",profundidad, btree_nnodos_profundidad(raiz, profundidad));
    printf("Profundidad del nodo que tiene el dato %d es %d\n",datoABuscar, btree_profundidad(raiz, &datoABuscar, (FuncionComparadora)comparacion));
    printf("La suma de los datos del arbol es %d\n", btree_sumar(raiz));
    btree_recorrer_bfs_recursivo(raiz, (FuncionVisitante) imprimirEntero);
    btree_destruir(raiz,destr);
    btree_destruir(arbolCopia,noDestr);
    return 0;
}