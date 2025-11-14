#ifndef __BTREE_H__
#define __BTREE_H__

typedef struct _BTNodo{
    void* dato;
    struct _BTNodo* left;
    struct _BTNodo* right;
} BTNodo;

typedef BTNodo* BTree;

typedef enum {
    BTREE_RECORRIDO_IN,
    BTREE_RECORRIDO_PRE,
    BTREE_RECORRIDO_POST
} BTreeOrdenDeRecorrido;

typedef void* (*FuncionCopia)(void*); 
typedef void(*FuncionDestructora)(void*);
typedef int (*FuncionComparadora)(void*, void*);
typedef void(*FuncionVisitante)(void*);
BTree btree_crear();

BTree btree_agregar_raiz(void*, FuncionCopia, BTree left, BTree right);

void btree_destruir(BTree tree, FuncionDestructora);

void btree_recorrer(BTree tree, BTreeOrdenDeRecorrido, FuncionVisitante);

int btree_buscar(BTree tree, void*, FuncionComparadora);

int btree_nnodos(BTree);

int btree_nnodos_profundidad(BTree, int);
BTree btree_copiar(BTree, FuncionCopia);

int btree_altura(BTree);

int btree_profundidad(BTree, void*, FuncionComparadora);

int btree_sumar(BTree);

void btree_recorrer_bfs_recursivo(BTree tree, FuncionVisitante visit);
#endif