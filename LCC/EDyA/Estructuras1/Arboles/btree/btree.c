#include "btree.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../Listas/Stack/stack.h"
#include "../../Listas/Queue/queue.h"
typedef struct _BTNodo{
  int dato;
  struct _BTNodo *left;
  struct _BTNodo *right;
}BTNodo;

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear() { return NULL; }

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo) {
  if (nodo != NULL) {
    btree_destruir(nodo->left);
    btree_destruir(nodo->right);
    free(nodo);
  }
}

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo) { return nodo == NULL; }

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(int dato, BTree left, BTree right) {
  BTree nuevoNodo = malloc(sizeof(struct _BTNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->dato = dato;
  nuevoNodo->left = left;
  nuevoNodo->right = right;
  return nuevoNodo;
}

void inorder(BTree arbol, FuncionVisitante visit){
  if(arbol == NULL){return;}
  inorder(arbol->left, visit);
  visit(arbol->dato);
  inorder(arbol->right,visit);
}

void preorder(BTree arbol, FuncionVisitante visit){
  if(arbol == NULL){return;}
  visit(arbol->dato);
  inorder(arbol->left, visit);
  inorder(arbol->right,visit);
}

void postorder(BTree arbol, FuncionVisitante visit){
  if(arbol == NULL){return;}
  inorder(arbol->left, visit);
  inorder(arbol->right,visit);
  visit(arbol->dato);
}
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitante visit){
  if(orden == BTREE_RECORRIDO_IN){
    printf("Inorder: ");
    inorder(arbol, visit);
    return;
  }
  if(orden == BTREE_RECORRIDO_PRE){
    printf("Preorder: ");
    preorder(arbol, visit);
    return;
  }
  printf("Postorder: ");
  postorder(arbol, visit);
  return;
}

void* noCopia(void* data){
  return data;
}

void noHagoNada(void* data){return;}
void recorrer_preorden_iterativo(BTree arbol, FuncionVisitante visit){
  Pila pila = pila_crear();
  // La funcion apilar debe devolver el mismo puntero, es decir, no realizar una copia fisica del dato
  pila = pila_apilar(pila, arbol, noCopia);

  printf("Preorder: ");

  while(!(pila_es_vacia(pila))){
    BTree nodo_actual = pila_tope(pila, noCopia);
    visit(nodo_actual->dato);
    // En desapilar, la funcion destroy debe retornar solamente para no liberar el dato de la pila (que es el mismo que el del arbol guardado en otro lugar)
    // En cambio, solo debe liberar el nodo de la pila
    pila = pila_desapilar(pila, noHagoNada);
    
    if(nodo_actual->right!=NULL){
      pila = pila_apilar(pila, nodo_actual->right, noCopia);
    }
    if(nodo_actual->left!=NULL){
      pila = pila_apilar(pila, nodo_actual->left, noCopia);
    }
  }
}

int maximo(int a,int b){
  return a >= b ? a : b;
}

int minimo(int a, int b){
  return a <= b ? a : b;
}
int constanteUno(int x){
  return x > 0 ? 1 : 0;
}
int btree_nnodos(BTree arbol){
  if(arbol==NULL){return 0;}
  return btree_nnodos(arbol->left) + btree_nnodos(arbol->right) + 1; 
}

int btree_buscar(BTree arbol, int dato){
  if(arbol == NULL){return 0;}
  if(arbol->dato == dato){return 1;}
  return (btree_buscar(arbol->left, dato) || btree_buscar(arbol->right, dato));
}

BTree btree_copiar(BTree arbol){
  if(arbol==NULL){
    return NULL;
}
    BTree nuevoArbol = btree_crear();
    nuevoArbol = btree_unir(arbol->dato, btree_copiar(arbol->left), btree_copiar(arbol->right));
    return nuevoArbol;
}


int btree_altura(BTree arbol){
  if(arbol==NULL){return -1;}
  return maximo(btree_altura(arbol->left) + 1, btree_altura(arbol->right)+1);
}

int btree_profundidad(BTree arbol, int dato, int profundidad){
  if(arbol == NULL) {return -1;}
  if(arbol->dato == dato){return profundidad;}
  return minimo(btree_profundidad(arbol->right, dato, profundidad + 1), btree_profundidad(arbol->left, dato, profundidad + 1));
}

int btree_nnodos_profundidad(BTree arbol, int profundidad){
  if(arbol == NULL){return 0;}
  if(profundidad == 0){return 1;}
  return btree_nnodos_profundidad(arbol->left, profundidad - 1) + btree_nnodos_profundidad(arbol->right, profundidad - 1);
}

int btree_sumar(BTree arbol){
  if(arbol==NULL){return 0;}
  return arbol->dato + btree_sumar(arbol->left) + btree_sumar(arbol->right);
}

void btree_recorrer_extra(BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitanteExtra visit, void* extra){
  if(arbol == NULL){return;}
  if(orden == BTREE_RECORRIDO_PRE){
    visit(arbol->dato, extra);
    btree_recorrer_extra(arbol->left, orden, visit, extra);
    btree_recorrer_extra(arbol->right, orden, visit, extra);
  }
  if(orden == BTREE_RECORRIDO_IN){
    btree_recorrer_extra(arbol->left, orden, visit, extra);
    visit(arbol->dato, extra);
    btree_recorrer_extra(arbol->right, orden, visit, extra);
  }
  if(orden == BTREE_RECORRIDO_POST){
    btree_recorrer_extra(arbol->left, orden, visit, extra);
    btree_recorrer_extra(arbol->right, orden, visit, extra);
    visit(arbol->dato, extra);
  }  
}

void btree_recorrer_bfs(BTree arbol, FuncionVisitante visit){
  Cola queue = cola_crear();
  cola_encolar(queue, arbol, noCopia);
  BTNodo* nodo_actual ;
  while(queue->first != NULL && queue->last!=NULL){
    nodo_actual = cola_primero(queue, noCopia);
      visit(nodo_actual->dato);
    if(nodo_actual->left !=NULL){
      cola_encolar(queue, nodo_actual->left, noCopia);
    }
    if(nodo_actual->right!=NULL){
      cola_encolar(queue, nodo_actual->right, noCopia);
    }
    cola_desencolar(queue, noHagoNada);
  }
}
/*
void btree_recorrer_bfsRecursivo(BTree arbol, FuncionVisitante visit){

}*/

int mayorDeMenores(BTree tree){
  if(tree->right == NULL){
    return tree->dato;
  }
  return mayorDeMenores(tree->right);
}

int menorDeMayores(BTree tree){
  if(tree->left == NULL){
    return tree->dato;
  }
  return mayorDeMenores(tree->left);
}
int btree_abb_validar(BTree tree){
  if(tree == NULL){return 1;}
  if(tree->left == NULL && tree->right == NULL){return 1;}
  if(btree_abb_validar(tree->left)){
    if(mayorDeMenores(tree->left) > tree->dato){
      return 0;
    }
  }
  if(btree_abb_validar(tree->right)){
    if(menorDeMayores(tree->right) < tree->dato){
      return 0;
    }
  }
  return 1;
/*  if(tree->left != NULL){
    if(tree->dato < tree->left->dato) return 0;
  }
  if(tree->right != NULL){
    if(tree->dato > tree->right->dato) return 0;
  }
*/
  //return btree_abb_validar(tree->left) && btree_abb_validar(tree->right);
}