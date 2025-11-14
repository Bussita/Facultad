#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>

typedef void (*FuncionVisitante)(void* dato);
typedef void* (*FuncionCopiadora)(void* dato);
typedef void (*FuncionDestructora)(void* dato);
typedef int (*FuncionComparadora)(void* dato1, void* dato2);
typedef unsigned int (*FuncionHash)(void* dato);

typedef struct _Matriz *Matriz;
typedef struct _AEF *AEF;

AEF aef_crear(int size);

void aef_destruir(AEF aef);

AEF aef_leer_archivo(FILE* file);

void aef_imprimir(AEF aef);

int aef_buscar_palabra(AEF aef, char* palabra);

#endif /* __MAIN_H__ */
