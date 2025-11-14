#include <stdlib.h>
#include "avl.h"
#include <assert.h>


AVL avl_crear(FuncionComparadora cmp, FuncionCopiadora copy, FuncionDestructora dest){
    AVL avltree = malloc(sizeof(struct _AVL));
    avltree->tree = NULL;
    avltree->cmp = cmp;
    avltree->copy = copy;
    avltree->dest = dest;
    return avltree;
}

void avl_arbol_destruir(AVLNodo* arbol, FuncionDestructora destroy){
    if(arbol == NULL){ return;}
    avl_arbol_destruir(arbol->left, destroy);
    avl_arbol_destruir(arbol->right, destroy);
    destroy(arbol->data);
    free(arbol);
}

void avl_destruir(AVL arbol){
    avl_arbol_destruir(arbol->tree, arbol->dest);
    free(arbol);
}

void avl_arbol_recorrer(AVLNodo* tree,AVL_ORDEN_RECORRIDO orden,FuncionVisitante visit){
    if(tree == NULL) return;
    if(orden == PREORDER) visit(tree->data);
    avl_arbol_recorrer(tree->left,orden,visit);
    if(orden == INORDER) visit(tree->data);
    avl_arbol_recorrer(tree->right,orden,visit);
    if(orden == POSTORDER) visit(tree->data);
}

void avl_recorrer(AVL avl, AVL_ORDEN_RECORRIDO orden, FuncionVisitante visit){
    avl_arbol_recorrer(avl->tree,orden,visit);
}

void* avl_arbol_buscar(AVLNodo* tree, void* data, FuncionComparadora cmp, FuncionCopiadora copy){
    if(tree == NULL) return NULL;
    if(cmp(tree->data, data)==0) return copy(tree->data);
    if(cmp(tree->data,data)<0){
        return avl_arbol_buscar(tree->right, data,cmp,copy);
    }
    return avl_arbol_buscar(tree->left,data,cmp,copy);
}

void* avl_buscar(AVL avl, void* data){
    return avl_arbol_buscar(avl->tree, data, avl->cmp, avl->copy);
}

int avl_nodo_altura(AVLNodo* tree){
    return (tree == NULL ? -1 : tree->altura);
}
int avl_nodo_factordebalance(AVLNodo* tree){
    assert(tree!=NULL);
    int factor = avl_nodo_altura(tree->left) - avl_nodo_altura(tree->right);
    assert(factor<=2 && factor>=-2);
    return factor;
}

int avl_max_altura_hijos(AVLNodo* tree){
    assert(tree!=NULL);
    int altIzq = avl_nodo_altura(tree->left);
    int altDer = avl_nodo_altura(tree->right);
    return (altIzq > altDer ? altIzq : altDer);
}
AVLNodo* avl_rotacion_simple_izq(AVLNodo* tree){
    AVLNodo* hijoDer = tree->right;
    tree->right = hijoDer->left;
    hijoDer->left = tree;
    tree->altura = 1 + avl_max_altura_hijos(tree);
    hijoDer->altura = 1 + avl_max_altura_hijos(hijoDer);
    return hijoDer;
}
AVLNodo* avl_rotacion_simple_der(AVLNodo* tree){
    AVLNodo* hijoIzq = tree->left;
    assert(hijoIzq!= NULL);
    tree->left = hijoIzq->right;
    hijoIzq->right = tree;
    tree->altura = 1 + avl_max_altura_hijos(tree);
    hijoIzq->altura = 1 + avl_max_altura_hijos(hijoIzq);
    return hijoIzq;
}

AVLNodo* avl_nodo_balancear(AVLNodo* tree){
    if(avl_nodo_factordebalance(tree)==-2){
        if(avl_nodo_factordebalance(tree->right)==1){
            tree->right = avl_rotacion_simple_der(tree->right);
        }
        tree = avl_rotacion_simple_izq(tree);
    }
    if(avl_nodo_factordebalance(tree)==2){
        if(avl_nodo_factordebalance(tree->left)==-1){
            tree->left = avl_rotacion_simple_izq(tree->left);
        }
        tree = avl_rotacion_simple_der(tree);
    }
    tree->altura = 1 + avl_max_altura_hijos(tree);
    return tree;
}

AVLNodo* avl_arbol_insertar(AVLNodo* arbol, FuncionComparadora cmp, FuncionCopiadora copy, void* data){
    if(arbol == NULL){
        AVLNodo* nuevoNodo = malloc(sizeof(AVLNodo));
        nuevoNodo->data = copy(data);
        nuevoNodo->altura = 0;
        nuevoNodo->left = nuevoNodo->right = NULL;
        return nuevoNodo;
    } else if(cmp(arbol->data,data)>=0){
        arbol->left = avl_arbol_insertar(arbol->left,cmp,copy,data);
        arbol = avl_nodo_balancear(arbol);
        return arbol;
    }else{
        arbol->right = avl_arbol_insertar(arbol->right,cmp,copy,data);
        arbol = avl_nodo_balancear(arbol);
        return arbol;
    }
}

AVL avl_insertar(AVL avl, void* data){
    avl->tree = avl_arbol_insertar(avl->tree,avl->cmp,avl->copy,data);
    return avl;
}


AVLNodo* nodoRemplazo(AVLNodo* nodo){
    if(nodo == NULL || (nodo->right == NULL && nodo->left == NULL)) return NULL;
    if(nodo->left == NULL || nodo->right == NULL){
        return nodo->left ? nodo->right : nodo->left;
    }
    AVLNodo* remplazo = nodo->right;
    if(remplazo->left == NULL) return remplazo;
    while(remplazo->left->left != NULL){
        remplazo = remplazo->left;
    }
    AVLNodo* padreRemplazo = remplazo;
    remplazo = remplazo->left;
    padreRemplazo->left = remplazo->right;
    remplazo->right = nodo->right;
    return remplazo;
}
AVLNodo* avl_arbol_eliminar(AVLNodo* arbol, FuncionComparadora cmp, FuncionDestructora dest, void* data){
    if(arbol == NULL) return NULL;
    if(cmp(arbol->data, data) == 0){
        AVLNodo *remplazo = nodoRemplazo(arbol);
        dest(arbol->data);
        free(arbol);
        return remplazo;
    }
    if(cmp(arbol->data,data)<0){
        arbol->right = avl_arbol_eliminar(arbol->right,cmp,dest,data);
        arbol = avl_nodo_balancear(arbol);
    }else{
        arbol->left = avl_arbol_eliminar(arbol->left, cmp,dest,data);
        arbol = avl_nodo_balancear(arbol);
    }
    return arbol;
}

AVL avl_eliminar(AVL avl, void* data){
    avl->tree = avl_arbol_eliminar(avl->tree, avl->cmp, avl->dest, data);
    return avl;
}

AVLNodo* mayorNodo(AVLNodo* tree){
    assert(tree!=NULL);
    if(tree->right == NULL) return tree;
    AVLNodo* mayor= tree->right;
    while(mayor->right!=NULL) mayor = mayor->right;
    return mayor;
}

AVLNodo* menorNodo(AVLNodo* tree){
    assert(tree!=NULL);
    if(tree->left == NULL) return tree;
    AVLNodo* menor = tree->left;
    while(menor->left!=NULL) menor = menor->left;
    return menor;
}

int avl_arbol_validar_abb(AVLNodo* tree, FuncionComparadora cmp){
    if(tree == NULL || (tree->left == NULL && tree->right == NULL)) return 1;
    if(avl_arbol_validar_abb(tree->left, cmp)){
        if(tree->left != NULL){
        AVLNodo* mayor = mayorNodo(tree->left);
        if(cmp(mayor->data, tree->data)==1) return 0;
        }
    }
    if(avl_arbol_validar_abb(tree->right, cmp)){
        if(tree->right!= NULL){
        AVLNodo* menor = menorNodo(tree->right);
        if(cmp(menor->data, tree->data)==-1) return 0;
        }
    }
    return 1; 
}

int avl_arbol_validar_alturaybalance(AVLNodo* tree){
    if(tree == NULL) return 1;
    
    int ret1 = avl_arbol_validar_alturaybalance(tree->left);
    int ret2 = avl_arbol_validar_alturaybalance(tree->right);
    if(ret1 && ret2){
        int altura = 1 + avl_max_altura_hijos(tree);
        int balance = avl_nodo_factordebalance(tree);
        if(tree->altura == altura && balance>=-1 && balance<=1) return 1;
    }
    return 0;
}

int avl_arbol_validar(AVLNodo* tree, FuncionComparadora cmp){
    if(avl_arbol_validar_abb(tree,cmp) && avl_arbol_validar_alturaybalance(tree)) return 1;
    return 0;
}

int avl_validar(AVL avl){
    return avl_arbol_validar(avl->tree, avl->cmp);
}

int avl_arbol_contarelementos(AVLNodo* tree){
    if(tree == NULL) return 0;
    return 1 + avl_arbol_contarelementos(tree->left) + avl_arbol_contarelementos(tree->right);
}
int avl_contarelementos(AVL avl){
    return avl_arbol_contarelementos(avl->tree);
}