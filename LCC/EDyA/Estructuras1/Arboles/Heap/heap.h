#ifndef __HEAP_H__
#define __HEAP_H__

typedef int (*FuncionComparadora) (void* dato, void* dato2);
typedef void (*FuncionDestructora) (void* dato);
typedef void (*FuncionVisitante) (void* dato);
typedef void* (*FuncionCopiadora) (void* dato);
typedef struct _BHeap{
    void** arr;
    int capacidad;
    int ultimo;
    FuncionComparadora comp;
} *BHeap;

BHeap bheap_crear(FuncionComparadora, int);

void bheap_destruir(BHeap, FuncionDestructora);

int bheap_es_vacio(BHeap);

void bheap_recorrer(BHeap, FuncionVisitante);

void bheap_insertar(BHeap, void*);

void bheap_eliminar(BHeap,void*, FuncionDestructora);

BHeap bheap_crear_desde_arr(void **arr, int largo, FuncionCopiadora copiar, FuncionComparadora cmp);

int bheap_validar(BHeap heap);

void heapsort(BHeap heap);
#endif
