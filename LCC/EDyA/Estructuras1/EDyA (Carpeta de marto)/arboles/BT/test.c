#include <stdio.h>
#include <stdlib.h>
#include "btree_int.h"


static void imprimir_entero(int data) {
  printf("%d ", data);
}


int main() {

  BTree ll = btree_unir(1, btree_crear(), btree_crear());
  BTree lr = btree_unir(3, btree_crear(), btree_crear());
  BTree rl = btree_unir(5, btree_crear(), btree_crear());
  BTree rr = btree_unir(7, btree_crear(), btree_crear());
  
  BTree l = btree_unir(2, ll, lr);
  BTree r = btree_unir(6, rl, rr);
  BTree raiz = btree_unir(4, l, r);

  btree_recorrer(raiz, BTREE_RECORRIDO_PRE, imprimir_entero);
  puts("");
  btree_recorrer_bfs(raiz, imprimir_entero);
  puts("");
  int cantidad = btree_recorrer_profundidad_dada(raiz, 3, imprimir_entero);
  puts("");
  printf("Cantidad visitados: %d\n",cantidad);
  
  printf("Cantidad nodos: %d\n", btree_cantidad_nodos(raiz));
  printf("Altura: %d\n", btree_altura(raiz));
  
  // Chequeamos busqueda y profundidad de nodos
  printf("Esta el 10?: %d\n", btree_buscar(raiz, 10));
  printf("Profundidad del 10: %d\n", btree_profundidad(raiz,10));
  printf("Esta el 5?: %d\n", btree_buscar(raiz, 5));
  printf("Profundidad del 5: %d\n", btree_profundidad(raiz,5));

  printf("Cantidad nodos a profundidad: %d\n", btree_cantidad_nodos_profundidad(raiz, 2));

  printf("Suma total: %d\n", btree_sumar(raiz));

  // Copiamos el arbol
  BTree arbol_copiado = btree_copiar(raiz);
  printf("IMPRIMIENDO ARBOL COPIA\n");
  btree_recorrer(arbol_copiado, BTREE_RECORRIDO_PRE, imprimir_entero);
  puts("");  


  btree_destruir(arbol_copiado);
  btree_destruir(raiz);

  return 0;
}
