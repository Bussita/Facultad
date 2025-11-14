#include "heap.h"
#include <stdlib.h>

// ###########################################################################
// Estructura de bajo nivel de Heap
struct _BHeap_bajo_nivel {

  void** arr;
  unsigned int capacidad;
  int ultimo;

};


typedef struct _BHeap_bajo_nivel* _BHeap;


static _BHeap _bheap_crear(int capacidad) {

  _BHeap bheap = malloc(sizeof(struct _BHeap_bajo_nivel));

  // Pedimos uno de mas ya que comenzamos a ordenar desde el 1
  bheap->arr = malloc(sizeof(void*) * (capacidad + 1));
  bheap->capacidad = capacidad;
  bheap->ultimo = 0;

  return bheap;
}


static void _bheap_destruir(_BHeap heap, FuncionDestructora destroy) {

  // Liberamos los elementos del heap
  for (int i = 1 ; i <= heap->ultimo ; i++)
    free(heap->arr[i]);

  // Liberamos donde almacenamos los elementos
  free(heap->arr);

  // Liberamos el heap
  free(heap);
}


static int _bheap_es_vacio(_BHeap heap) { return heap->ultimo == 0; }


static void _bheap_recorrer(_BHeap heap, FuncionVisistante visit) {

  for (int i = 1 ; i <= heap->ultimo ; i++)
    visit(heap->arr[i]);
}


static void heapify(void** arr, int largo, int objetivo, FuncionComparadora comp) {

  // Consideramos que la numeracion comeienza desde el 0

  int max = objetivo; 

  int hijo_izquierda = objetivo * 2 + 1; // Calculamos los dos hijos
  int hijo_derecha = objetivo * 2 + 2;

  // Vemos por cual hijo vamos a bajar
  if (hijo_izquierda < largo && comp(arr[hijo_izquierda], arr[max]) > 0)    
    max = hijo_izquierda;

  if (hijo_derecha < largo && comp(arr[hijo_derecha], arr[max]) > 0)
    max = hijo_derecha;

  if (max != objetivo) { // Solo hacemos Swap si podemos bajar

    void* intercambio = arr[max];
    arr[max] = arr[objetivo];
    arr[objetivo] = intercambio; 

    heapify(arr, largo, max, comp); // Seguimos bajando al elemento
  }  
}


static void _bheap_insertar(_BHeap heap, void* dato, FuncionCopiar copiar,
                                                     FuncionComparadora comp) {

  // Primero nos fijamos si tenemos que redimensionar el heap
  if (heap->ultimo == heap->capacidad) {
    
    heap->capacidad = heap->capacidad * 2 - 1;
    heap->arr = realloc(heap->arr, sizeof(void*) * heap->capacidad);
  }

  // Insertamos a lo ultimo 
  heap->ultimo ++;
  heap->arr[heap->ultimo] = copiar(dato);

  // Ahora tenemos que reacomodarlo para que se siga cumpliendo la condicion de heap
  int indice_insertado = heap->ultimo;
  int indice_padre = indice_insertado / 2;

  while (indice_insertado != 1 && 
         comp(heap->arr[indice_insertado], heap->arr[indice_padre]) > 0) {

    void* intercambio = heap->arr[indice_insertado];
    heap->arr[indice_insertado] = heap->arr[indice_padre];
    heap->arr[indice_padre] = intercambio;

    indice_insertado = indice_padre;
    indice_padre = indice_insertado / 2;
  }

}


static void _bheap_eliminar(_BHeap heap, FuncionDestructora destroy,
                                         FuncionComparadora comp) {

  if (_bheap_es_vacio(heap)) return;

  // Eliminamos el primero
  destroy(heap->arr[1]); 

  // Movemos el ultimo al primero
  heap->arr[1] = heap->arr[heap->ultimo];
  heap->ultimo --;

  // Hacemos descender al dato hasta una posicion adecuada
  heapify(heap->arr + 1, heap->ultimo, 0, comp);
}


static void* _bheap_maximo(_BHeap heap, FuncionCopiar copiar) {
  
  if (_bheap_es_vacio(heap)) return NULL;

  return copiar(heap->arr[1]);
}


// ############################################################################
// Estructura de alto nivel de Heap, que incluye las funciones de comparacion,
// copiado y destruccion de datos.
struct _BHeap_alto_nivel {

  _BHeap data;
  FuncionComparadora comp;
  FuncionCopiar copiar;
  FuncionDestructora dest;

};


BHeap bheap_crear(int capacidad, FuncionComparadora comp,
                                 FuncionCopiar copiar,
                                 FuncionDestructora dest) {

  BHeap bheap = malloc(sizeof(struct _BHeap_alto_nivel));

  bheap->data = _bheap_crear(capacidad);
  bheap->comp = comp;
  bheap->copiar = copiar;
  bheap->dest = dest;

  return bheap;
}


void bheap_destruir(BHeap heap) {

  _bheap_destruir(heap->data, heap->dest);
  free(heap);
}


int bheap_es_vacio(BHeap heap) { return _bheap_es_vacio(heap->data); }


void bheap_recorrer(BHeap heap, FuncionVisistante visit) {

  
 _bheap_recorrer(heap->data, visit);
}


void bheap_insertar(BHeap heap, void* dato) {

  _bheap_insertar(heap->data, dato, heap->copiar, heap->comp);
}


void bheap_eliminar(BHeap heap) {

  _bheap_eliminar(heap->data, heap->dest, heap->comp);
}


void* bheap_maximo(BHeap heap) {

  return _bheap_maximo(heap->data, heap->copiar);
}



BHeap bheap_crear_desde_arr(void** arr, int largo, FuncionCopiar copiar,
                                                   FuncionComparadora comp,
                                                   FuncionDestructora dest) {

  // Creo un nuevo BHeap de alto nivel
  BHeap heap = malloc(sizeof(struct _BHeap_alto_nivel));

  heap->copiar = copiar;
  heap->comp = comp;
  heap->dest = dest;

  // Pedimos memoria para el lugakr vacio del principio
  void** copiaArreglo = malloc(sizeof(void*) * (largo + 1));

  // Copiamos los elementos, ya no queremos modificar el arreglo oroginal
  for (int i = 1 ; i <= largo ; i++)
    copiaArreglo[i] = copiar(arr[i - 1]); 
  
  // Convertimos al arreglo en heap, a partir del elemento en la pos 1
  for (int i = largo / 2 - 1 ; i >= 0 ; i--)
    
    heapify(copiaArreglo + 1, largo, i, comp);

  // Completamos el heap a bajo nivel y lo devolvemos
  heap->data = malloc(sizeof(struct _BHeap_bajo_nivel));
  heap->data->arr = copiaArreglo;
  heap->data->ultimo = largo;
  heap->data->capacidad = largo;

  return heap;
}


void heap_sort(void** arr, int largo, FuncionComparadora comp) {

  // Creo un heap
  for (int i = largo / 2 - 1 ; i >= 0 ; i--)    
    heapify(arr, largo, i, comp);

  // Mando el primero del heap a lo ultimo, y convierto en un heap la primera parte 
  for (int i = largo - 1 ; i >= 0 ; i--) {

    void* intercambio = arr[0];
    arr[0] = arr[i];
    arr[i] = intercambio; 

    heapify(arr, i , 0, comp);
  }
}