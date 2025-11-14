#ifndef __MATRIZ_H__
  
#define __MATRIZ_H__

#include <stdlib.h>
#include <stdio.h>

typedef struct Matriz_implementation Matriz;

Matriz* crear_matriz(int cant_filas, int cant_columnas);

void destruir_matriz(Matriz* matriz);

float leer_matriz(Matriz* matriz, int columna, int fila);

void mostrar_matriz(Matriz* matriz);

void escribir_matriz(Matriz* matriz, int fila, int columna, float nuevo_dato);

int cantidad_filas_matriz(Matriz* matriz);

int cantidad_columnas_matriz(Matriz* matriz);

void intercambiar_filas_matriz(Matriz* matriz, int fila1, int fila2);

void insertar_fila_matriz(Matriz* matriz, int fila);

#endif /* __MATRIZ_H__ */
