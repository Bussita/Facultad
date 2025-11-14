#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

typedef void* (*FuncionCopia)(void*, void*);
typedef void (*FuncionVisitante)(void*);
typedef void (*FuncionDestructora)(void*);
typedef int (*FuncionComparadora)(void*, void*);

// -----------------------------------------

typedef struct _MatrizAux* MatrizAux;
typedef struct _Matriz* Matriz;


// --------------

MatrizAux matriz_crear(int n);

int matriz_leer(MatrizAux matriz, int i, int j);

void matriz_imprimir(MatrizAux matriz);

void matriz_destruir(MatrizAux matriz);
#endif