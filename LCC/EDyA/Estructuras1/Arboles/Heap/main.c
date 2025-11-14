#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

static void imprimir_entero(int* i){
    printf("%d ",*i);
}

int compararPorMayor(int* dato, int* dato2){
    if(*dato > *dato2) return 1;
    if(*dato == *dato2) return 0;
    return -1;
}

void destruyo(void* dato){
    free(dato);
}

int* Copia(int* dato){
    int* copia = malloc(sizeof(int));
    *copia = *dato;
    return copia;
}
int main(){
    BHeap heap = bheap_crear((FuncionComparadora) compararPorMayor, 1);
    int* a = malloc(sizeof(int));
    *a = 10;
    bheap_insertar(heap, a);
    int* b = malloc(sizeof(int));
    *b = 20;
    bheap_insertar(heap, b);
    int* c = malloc(sizeof(int));
    *c = 15;
    bheap_insertar(heap, c);
    int* d = malloc(sizeof(int));
    *d = 25;
    bheap_insertar(heap, d);
    int* e = malloc(sizeof(int));
    *e = 30;
    bheap_insertar(heap, e);
    bheap_recorrer(heap, (FuncionVisitante) imprimir_entero);
    bheap_eliminar(heap, e, destruyo);
    bheap_eliminar(heap, d, destruyo);
    printf("\n");
    //bheap_recorrer(heap, (FuncionVisitante) imprimir_entero);
    int** arr = malloc(sizeof(int*)*100);
    puts("");
    for(int i=0; i<10000; i++){
        int* a = malloc(sizeof(int));
        *a = rand() % 1000;
        arr[i] = a;
    }
    puts("");
    BHeap heapdesdeArray = bheap_crear_desde_arr((void **)arr,10000,(FuncionCopiadora) Copia, (FuncionComparadora) compararPorMayor);
    //heapsort(heapdesdeArray);
    bheap_recorrer(heapdesdeArray, (FuncionVisitante) imprimir_entero);
    if(bheap_validar(heapdesdeArray)==1){
        printf("\nEs heap\n");
    }else{
        printf("\n No es heap\n");
    }
    free(arr);
    bheap_destruir(heap, (FuncionDestructora) destruyo);
    bheap_destruir(heapdesdeArray, (FuncionDestructora) destruyo);
    return 0;
}