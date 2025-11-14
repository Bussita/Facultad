#ifndef __MAIN_H__
#define __MAIN_H__

#define FACTOR_MAXIMO_CARGA 0.7

typedef void (*FuncionVisitante)(void* dato);
typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void *dato1, void *dato2);
typedef void (*FuncionDestructora)(void *dato);
typedef unsigned int (*FuncionHash)(void *dato);

//////////////////////////////////

typedef struct _TablaHash *TablaHash;

typedef struct _Matriz *MatrizAux;

typedef struct _Persona Persona;

//////////////////////////////////

TablaHash tablahash_crear(unsigned int size, FuncionCopiadora copy, FuncionDestructora destroy ,FuncionComparadora comp, FuncionHash hash);

unsigned int tablahash_nelems(TablaHash tabla);

unsigned int tablahash_size(TablaHash tabla);

void tablahash_destruir(TablaHash tabla);

void tablahash_insertar(TablaHash tabla, void *dato, int persona, MatrizAux matriz);

void tablahash_recorrer(TablaHash tabla, FuncionVisitante visit);

//////////////////////////////////

MatrizAux matriz_crear(int filas, int cols);

void matriz_escribir(MatrizAux matirz, int dato, int fila, int col);

int matriz_leer(MatrizAux matriz, int fila, int col);

int matriz_contar_dato(MatrizAux matriz, int dato);

void matriz_destruir(MatrizAux matriz);

void matriz_imprimir(MatrizAux matriz);

//////////////////////////////////

int contar_amistades(Persona* personas, int cantPersonas);

Persona* leer_datos(char* path, int* cantPersonas);

void persona_destruir(Persona persona);

void personas_destruir(Persona* personas, int cantPersonas);

void personas_imprimir(Persona* personas, int cant_personas);

#endif