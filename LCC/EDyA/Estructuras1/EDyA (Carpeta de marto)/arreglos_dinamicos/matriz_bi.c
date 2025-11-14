#include "matriz.h"

struct Matriz_implementation {
  
  float** elementos;
  int numero_columnas;
  int numero_filas;

};


Matriz* crear_matriz(int cantidad_filas, int cantidad_columnas) {

  Matriz* nueva_matriz = malloc(sizeof(Matriz));

  nueva_matriz->elementos = malloc(sizeof(float*) * cantidad_filas);

  // Pedimos espacio para las filas e inicializamos sus valores
  for (int i = 0 ; i < cantidad_filas ; i++) {
    nueva_matriz->elementos[i] = malloc(sizeof(float) * cantidad_columnas);

    for (int j = 0 ; j < cantidad_columnas ; j++) 
      nueva_matriz->elementos[i][j] = 1;
  }

  nueva_matriz->numero_columnas = cantidad_columnas;
  nueva_matriz->numero_filas = cantidad_filas;

  return nueva_matriz;
}



void destruir_matriz(Matriz* matriz) {

  for (int i = 0 ; i < matriz->numero_filas ; i++)
    free(matriz->elementos[i]);

  free(matriz->elementos);

  free(matriz);
}



float leer_matriz(Matriz* matriz, int columna, int fila) {

  // Si esta fuera de rango, no queda determinado el comportamiento
  return matriz->elementos[fila][columna];
}


void mostrar_matriz(Matriz* matriz) {

  for (int i = 0 ; i < matriz->numero_filas ; i++) {

    for (int j = 0 ; j < matriz->numero_columnas ; j++)

      printf("%.1f  ",matriz->elementos[i][j]);

    printf("\n");
  }

}


void escribir_matriz(Matriz* matriz, int fila, int columna, float nuevo_dato) {

  // Si esta fuera de rango, no queda determinado el comportamiento.
  matriz->elementos[fila][columna] = nuevo_dato;
}

int cantidad_filas_matriz(Matriz* matriz) {

  return matriz->numero_filas;  
}

int cantidad_columnas_matriz(Matriz* matriz) {

  return matriz->numero_columnas;
}

void intercambiar_filas_matriz(Matriz* matriz, int fila1, int fila2) {

  // Consideramos que el valor de las filas a intercambiar es correcto.

  float* fila_intercambio = matriz->elementos[fila1];

  matriz->elementos[fila1] = matriz->elementos[fila2];

  matriz->elementos[fila2] = fila_intercambio;
}



void insertar_fila_matriz(Matriz* matriz, int fila) {

  // Consideramos que el valor de la posicion de la fila a insertar
  // se encuentra dentro del rango de la matriz.

  // Pedimos espacio para una nueva fila
  float** nuevos_elementos = malloc(sizeof(float*) * (matriz->numero_filas + 1));
  float* nueva_fila = malloc(sizeof(float) * matriz->numero_columnas);

  // Copiamos los elementos al nuevo espacio en memoeria
  for (int i = 0 ; i < matriz->numero_filas ; i++) {

    if (i < fila)
      nuevos_elementos[i] = matriz->elementos[i];

    else
      nuevos_elementos[i + 1] = matriz->elementos[i];
  }
  // Inicializamos la nueva fila y la agregamos
  for (int j = 0 ; j < matriz->numero_columnas ; j++)
    nueva_fila[j] = 0;
 
  nuevos_elementos[fila] = nueva_fila;
  
  free(matriz->elementos);

  // Liberamos los antiguos valore y copiamos los nuevos 
  matriz->elementos = nuevos_elementos;
  matriz->numero_filas++;

    
}