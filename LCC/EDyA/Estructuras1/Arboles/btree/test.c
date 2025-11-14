#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

static void imprimir_entero(int data) {
  printf("%d ",data);
}

int main() {
  setbuf(stdout, NULL);
  BTree ll = btree_unir(1, btree_crear(), btree_crear());
  BTree l = btree_unir(2, ll, btree_crear());
  BTree r = btree_unir(3, btree_crear(), btree_crear());
  BTree raiz = btree_unir(4, l, r);
  int dato = 10;
  btree_recorrer(raiz, BTREE_RECORRIDO_POST, imprimir_entero);
  btree_recorrer(raiz, BTREE_RECORRIDO_IN, imprimir_entero);
  btree_recorrer(raiz, BTREE_RECORRIDO_PRE, imprimir_entero);
  printf("La altura del arbol es %d\n", btree_altura(raiz));
  printf("La profundidad del dato %d en el arbol es %d\n",dato, btree_profundidad(raiz, dato,0));
  printf("La suma de los datos del arbol es %d\n",btree_sumar(raiz));
  printf("BSF: ");
  btree_recorrer_bfs(raiz, imprimir_entero);
  puts("");
  BTree II = btree_unir(1, btree_crear(), btree_crear());
  BTree ID = btree_unir(3, btree_crear(), btree_crear());
  BTree I = btree_unir(5, II, ID);
  BTree D = btree_unir(2, btree_crear(), btree_crear());
  BTree arbol2 = btree_unir(4, I, D);
  printf("\n Arbol inorder: ");
  btree_recorrer(arbol2,BTREE_RECORRIDO_IN, imprimir_entero);
  printf("\n");
  int esAbb = btree_abb_validar(arbol2);
  if(esAbb == 1){
    printf("\nEl arbol es ABB");
  }else{
    printf("\nEl arbol no es ABB");
  }
  btree_destruir(raiz);
  return 0;
}
