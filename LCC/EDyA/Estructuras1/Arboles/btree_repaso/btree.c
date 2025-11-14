#include "btree.h"
#include <stdlib.h>
#include <assert.h>


BTree btree_crear(){return NULL;}

BTree btree_agregar_raiz(void* dato, FuncionCopia copy, BTree left, BTree right){
    BTree nuevoNodo = malloc(sizeof(BTNodo));
    assert(nuevoNodo!=NULL);
    nuevoNodo->dato = copy(dato);
    nuevoNodo->left = left;
    nuevoNodo->right = right;
    return nuevoNodo;
}

void btree_destruir(BTree tree, FuncionDestructora destroy){
    if(tree == NULL) return;
    btree_destruir(tree->left,destroy);
    btree_destruir(tree->right, destroy);
    destroy(tree->dato);
    free(tree);
}

int btree_buscar(BTree tree,void* dato,FuncionComparadora cmp){
    if(tree==NULL) return 0;
    if(cmp(tree->dato, dato)==0) return 1;
    return btree_buscar(tree->left,dato,cmp) || btree_buscar(tree->right,dato,cmp);
}

void btree_recorrer(BTree tree, BTreeOrdenDeRecorrido orden, FuncionVisitante visit){
    if(tree == NULL) return;
    if(orden == BTREE_RECORRIDO_PRE) visit(tree->dato);
    btree_recorrer(tree->left, orden, visit);
    if(orden == BTREE_RECORRIDO_IN) visit(tree->dato);
    btree_recorrer(tree->right, orden, visit);
    if(orden == BTREE_RECORRIDO_POST) visit(tree->dato);
}

int btree_nnodos(BTree tree){
    if(tree == NULL) return 0;
    return 1+btree_nnodos(tree->left)+btree_nnodos(tree->right);
}

BTree btree_copiar(BTree tree, FuncionCopia copy){
    if(tree == NULL){ return NULL;}
    return btree_agregar_raiz(tree->dato,copy,btree_copiar(tree->left,copy), btree_copiar(tree->right,copy));
}

static int max(int a, int b){
    return a<=b? b : a;
}

int btree_altura(BTree tree){
    if(tree == NULL) return -1;
    if(tree->left == NULL && tree->right == NULL) return 0;
    return 1 + max(btree_altura(tree->left), btree_altura(tree->right));
}

int btree_nnodos_profundidad(BTree tree, int k){
    if(tree == NULL) return 0;
    if(k == 0) return 1;
    return btree_nnodos_profundidad(tree->left, k-1) + btree_nnodos_profundidad(tree->right, k-1);
}

/*static int min(int a, int b){
    return a<=b? a:b;
}
*/

// Anda mal, hay que chequear, la otra forma es mas facil pero tiene detalles.
static int btree_profundidad_aux(BTree tree, int* k, void* dato, FuncionComparadora cmp){
    if(tree == NULL){
        *k = -1;
        return -1;
    }
    if(cmp(tree->dato,dato)==0){
        *k = 0;
        return 0;
    }
    int p1 = 1 + btree_profundidad_aux(tree->left, k, dato, cmp);
    int p2 = 1 + btree_profundidad_aux(tree->right, k, dato, cmp);
    *k = max(p1,p2);
    return *k;
}

int btree_profundidad(BTree tree, void* dato, FuncionComparadora cmp){
    int prof = 0;
    return btree_profundidad_aux(tree,&prof,dato,cmp);
}

int btree_sumar(BTree tree){
    if(tree==NULL) return 0;
    return *(int*)tree->dato + btree_sumar(tree->right) + btree_sumar(tree->left); 
}

void visitoSoloAProfundidadK(BTree tree, FuncionVisitante visit, int prof){
    if(tree == NULL) return;
    if(prof == 0){
        visit(tree->dato);
        return;
    }
    visitoSoloAProfundidadK(tree->left, visit, prof - 1);
    visitoSoloAProfundidadK(tree->right, visit, prof - 1);
    return;
}

void btree_recorrer_bfs_recursivo(BTree tree, FuncionVisitante visit){
    int prof = 0, status = 1;
    while(status){
        if(btree_nnodos_profundidad(tree, prof) == 0){
            status = 0;
        }else{
            visitoSoloAProfundidadK(tree, visit, prof);
            prof++;
        }
    }
}