#ifndef __HEAP_H__
#define __HEAP_H__

typedef int (*FuncionComparadora) (void*, void*);
typedef void (*FuncionDestructora) (void*);
typedef void* (*FuncionCopiar) (void*);
typedef void (*FuncionVisistante) (void*);


typedef struct _BHeap_alto_nivel* BHeap; 


BHeap bheap_crear(int capacidad, FuncionComparadora comp,
                                 FuncionCopiar copiar,
                                 FuncionDestructora dest);

void bheap_destruir(BHeap heap);

int bheap_es_vacio(BHeap heap);

void bheap_recorrer(BHeap heap, FuncionVisistante visit);

void bheap_insertar(BHeap heap, void* dato);

void bheap_eliminar(BHeap heap);

void* bheap_maximo(BHeap heap);

BHeap bheap_crear_desde_arr(void** arr, int largo, FuncionCopiar copiar,
                                                   FuncionComparadora comp,
                                                   FuncionDestructora dest);

void heap_sort(void** arr, int largo, FuncionComparadora comp);

#endif /* __HEAP_H__ */