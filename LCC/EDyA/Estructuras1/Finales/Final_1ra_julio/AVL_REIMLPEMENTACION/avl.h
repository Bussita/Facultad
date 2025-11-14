#ifndef __AVL_H__
#define __AVL_H__

typedef void* (*FuncionCopiadora)(void*);
typedef void (*FuncionDestructora)(void*);
typedef int (*FuncionComparadora)(void*, void*);
typedef void(*FuncionVisitante)(void*);

typedef struct _AVLNodo{
    void* data;
    struct _AVLNodo* right, *left;
    int altura;
}AVLNodo;


struct _AVL{
    AVLNodo* tree;
    FuncionComparadora cmp;
    FuncionCopiadora copy;
    FuncionDestructora dest;
};

typedef struct _AVL* AVL;

AVL avl_crear(FuncionComparadora, FuncionCopiadora, FuncionDestructora);

void avl_destruir(AVL arbol);

typedef enum{
    PREORDER,
    INORDER,
    POSTORDER
}AVL_ORDEN_RECORRIDO;

void avl_recorrer(AVL, AVL_ORDEN_RECORRIDO, FuncionVisitante);

void* avl_buscar(AVL, void*);

AVL avl_insertar(AVL avl, void* data);

AVL avl_eliminar(AVL avl, void* data);

int avl_validar(AVL avl);

int avl_contarelementos(AVL avl);
#endif