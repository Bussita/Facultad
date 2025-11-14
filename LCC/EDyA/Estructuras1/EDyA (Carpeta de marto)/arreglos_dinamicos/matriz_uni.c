#include "matriz.h"

struct Matriz_implementation {
  
  float* elementos;
  int numero_columnas;
  int numero_filas;

};



Matriz* crear_matriz(int cantidad_filas, int cantidad_columnas) {

  Matriz* nueva_matriz = malloc(sizeof(Matriz));

  nueva_matriz->elementos = malloc(sizeof(float) * (cantidad_filas * cantidad_columnas));

  // Inicializamos los valores a 0
  int largo_total = cantidad_filas * cantidad_columnas;

  for (int i = 0 ; i < largo_total ; i++)
    nueva_matriz->elementos[i] = 1;

  nueva_matriz->numero_columnas = cantidad_columnas;
  nueva_matriz->numero_filas = cantidad_filas;

  return nueva_matriz;
}



void destruir_matriz(Matriz* matriz) {

  free(matriz->elementos);
  free(matriz);
}



float leer_matriz(Matriz* matriz, int columna, int fila) {

  // Si esta fuera de rango, no queda determinado el comportamiento
  return matriz->elementos[matriz->numero_columnas * fila + columna];
}



void mostrar_matriz(Matriz* matriz) {

  for (int i = 0 ; i < matriz->numero_filas ; i++) {

    for (int j = 0 ; j < matriz->numero_columnas ; j++) 

      printf("%.1f  ", matriz->elementos[matriz->numero_columnas * i + j]);    

    printf("\n");
  }
}



void escribir_matriz(Matriz* matriz, int fila, int columna, float nuevo_dato) {

  // Si esta fuera de rango, no queda determinado el comportamiento
  matriz->elementos[matriz->numero_columnas * fila + columna] = nuevo_dato;
}



int cantidad_filas_matriz(Matriz* matriz) {

  return matriz->numero_filas;
}



int cantidad_columnas_matriz(Matriz* matriz) {

  return matriz->numero_columnas;
}



void intercambiar_filas_matriz(Matriz* matriz, int fila1, int fila2) {

  float buffer;

  for (int i = 0 ; i < matriz->numero_columnas ; i++){

    buffer = matriz->elementos[matriz->numero_columnas * fila1 + i];
    matriz->elementos[matriz->numero_columnas * fila1 + i] = matriz->elementos[matriz->numero_columnas * fila2 + i];
    matriz->elementos[matriz->numero_columnas * fila2 + i] = buffer; 
  }
}



void insertar_fila_matriz(Matriz* matriz, int fila) {

  // Pedimos memoria para la nueva fila
  float* nuevos_elementos = malloc(sizeof(float) * (matriz->numero_columnas * (matriz->numero_filas + 1)));

  // Copiamos todos los elementos
  for (int i = 0 ; i < matriz->numero_filas ; i++) {

    for (int j = 0 ; j < matriz->numero_columnas ; j++) {

      if (i < fila)
        nuevos_elementos[matriz->numero_columnas * i + j] = matriz->elementos[matriz->numero_columnas * i + j];

      else
        nuevos_elementos[matriz->numero_columnas * (i + 1) + j] = matriz->elementos[matriz->numero_columnas * i + j];
    }
  }

  // Inicializamos la nueva fila agrega
  for (int j = 0 ; j < matriz->numero_columnas ; j++) 
    nuevos_elementos[matriz->numero_columnas * fila + j] = 0;

  free(matriz->elementos);

  matriz->elementos = nuevos_elementos;
  matriz->numero_filas ++;
}