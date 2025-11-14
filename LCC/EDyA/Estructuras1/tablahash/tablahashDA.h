#ifndef __TABLAHASHDA_H_
#define __TABLAHASHDA_H_


typedef void *(*FuncionCopiadora)(void *dato);

typedef int (*FuncionComparadora)(void *dato1, void *dato2);

typedef void (*FuncionDestructora)(void *dato);

typedef unsigned (*FuncionHash)(void *dato);

typedef struct _TablaHash *TablaHash;

TablaHash tablahash_crear(unsigned capacidad, FuncionCopiadora copy, FuncionComparadora cmp, FuncionDestructora destr, FuncionHash hash);

unsigned int tablahash_capacidad(TablaHash tabla);

unsigned int tablahash_numeroDeElementos(TablaHash tabla);

float tablahash_factorDeCarga(TablaHash tabla);

void tablahash_destruir(TablaHash tabla);

void tablahash_insertar(TablaHash tabla, void*);

void* tablahash_buscar(TablaHash, void*);

void tablahash_redimensionar(TablaHash);

void tablahash_eliminar(TablaHash tabla, void* dato);

#endif