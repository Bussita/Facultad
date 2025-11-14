#include <stdlib.h>
#include "heap.h"
#include <stdio.h>
/*
static int potencia(int a, int b){
    if(b == 1){
     return a;   
    }else{
        return a * potencia(a, b-1);
    }
}
*/
BHeap bheap_crear(FuncionComparadora comparar, int capacidad){
    BHeap nuevoHeap = malloc(sizeof(struct _BHeap));
    nuevoHeap->arr = malloc(sizeof(void*)*capacidad);
    nuevoHeap->capacidad = capacidad;
    nuevoHeap->ultimo = 0;
    nuevoHeap->comp = comparar;
    return nuevoHeap;
}

void bheap_destruir(BHeap heap, FuncionDestructora destroy){
    if(!(bheap_es_vacio(heap))){
        for(int i=1; i<=heap->ultimo; i++){
            destroy (heap->arr[i]);
        }
    }
    free(heap->arr);
    free(heap);
}

int bheap_es_vacio(BHeap heap){
    if(heap->ultimo == 0){
        return 1;
    }else{
        return 0;
    }
}

void bheap_recorrer(BHeap heap, FuncionVisitante visit){
    for(int i=1; i<=heap->ultimo; i++) {
        visit(heap->arr[i]);
}
}
// Dado el indice de un dato, lo hace ascender hasta su posicion en el heap;
void bheap_flotar(BHeap heap, int indice){
    int i = indice;
    while(i>1 && heap->comp(heap->arr[i],heap->arr[i/2])==1){
        void* aux = heap->arr[i/2];
        heap->arr[i/2] = heap->arr[i];
        heap->arr[i] = aux;
        i/=2;
    }
}
// Dado el indice de un dato, lo hace descender hasta su posicion en el heap;
void bheap_hundir(BHeap heap, int indice){
    int esMayor = 1;
    int i = indice;
    while((2*i)<=heap->ultimo && esMayor){
        int k = 2*i;
        if(k+1<=heap->ultimo && heap->comp(heap->arr[k+1],heap->arr[k])==1) k = k+1;
        if(heap->comp(heap->arr[i],heap->arr[k])==1){
            esMayor = 0;
        }else{
            void* aux = heap->arr[k];
            heap->arr[k] = heap->arr[i];
            heap->arr[i] = aux;
            i = k;
        }
    }
}
void bheap_insertar(BHeap heap, void* dato){
    if(heap->ultimo == heap->capacidad - 1){
        heap->capacidad*=2;
        heap->arr = realloc(heap->arr,sizeof(void*)*heap->capacidad);
    }
    heap->ultimo++;
    heap->arr[heap->ultimo] = dato;
    bheap_flotar(heap, heap->ultimo);
}

void bheap_eliminar(BHeap heap, void* dato, FuncionDestructora destroy){
    int i=1;
    while(heap->comp(heap->arr[i], dato)!=0) i++;
    void* datoADestruir = heap->arr[i];
    heap->arr[i] = heap->arr[heap->ultimo];
    heap->ultimo--;
    destroy(datoADestruir);
    bheap_hundir(heap, i);
}

/*void heapify(void** arr, int largo, int indice, FuncionComparadora cmp, FuncionCopiadora copy){
    int mayor = indice;
    int hijoIzq = 2*indice;
    int hijoDer = 2*indice +1;

    if(hijoIzq < largo && cmp(arr[hijoIzq],arr[mayor])==1) mayor = hijoIzq;
    if(hijoDer < largo && cmp(arr[hijoDer],arr[mayor])==1) mayor = hijoDer;
    if(mayor != indice){
        void* aux = copy(arr[indice]);
        arr[indice] = copy(arr[mayor]);
        arr[mayor] = copy(aux);
        heapify(arr, largo, mayor, cmp, copy);
    }
}*/

static void swapInt(int* x, int* y){
    int aux = *x;
    *x = *y;
    *y = aux;
}

BHeap bheap_crear_desde_arr(void** arr, int largo, FuncionCopiadora copiar, FuncionComparadora cmp){
    BHeap nuevoHeap = bheap_crear(cmp,largo);
    nuevoHeap->ultimo = largo-1;
    for(int i = largo-1; i>=1; i--){
        nuevoHeap->arr[i] = copiar(arr[i]);
        if(i!=largo){
            bheap_hundir(nuevoHeap, i);
        }
    }
    int n = nuevoHeap->ultimo;
    while(nuevoHeap->ultimo>=2){
        swapInt(nuevoHeap->arr[1],nuevoHeap->arr[nuevoHeap->ultimo]);
        nuevoHeap->ultimo--;
        bheap_hundir(nuevoHeap,1);
    }
    nuevoHeap->ultimo = n;
    return nuevoHeap;
}

int bheap_validar(BHeap heap){
    for(int i = 1; i<=heap->ultimo; i++){
        if(2*i <=heap->ultimo && heap->comp(heap->arr[i], heap->arr[2*i])==-1){
            return 0;
        } else if(2*i + 1 <=heap->ultimo && heap->comp(heap->arr[i], heap->arr[2*i + 1])==-1){
            return 0;
        }
    }
    return 1;
}