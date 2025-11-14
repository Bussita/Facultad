#include "matriz.h"
#include <stdio.h>


int main(void) {

  Matriz* matriz = crear_matriz(3,4);

  mostrar_matriz(matriz);

  insertar_fila_matriz(matriz, 1);
  
  printf("\n");

  mostrar_matriz(matriz);

  intercambiar_filas_matriz(matriz,1,2);

  printf("\n");

  mostrar_matriz(matriz);

  destruir_matriz(matriz);

  return 0;
}