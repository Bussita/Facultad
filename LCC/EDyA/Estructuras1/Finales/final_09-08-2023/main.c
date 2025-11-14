#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

typedef struct {
  int a;
  int b;
} CasillaMatriz;

struct _Matriz {
  CasillaMatriz** arr;
  int size;
};

struct _AEF {
  Matriz matriz;
  int* na;
};

static Matriz matriz_crear(int size) {
  Matriz matriz = malloc(sizeof(struct _Matriz));

  matriz->size = size;

  matriz->arr = malloc(sizeof(CasillaMatriz*) * size);

  for (int i = 0; i < size; i++) {
    matriz->arr[i] = malloc(sizeof(CasillaMatriz) * size);
    
    for (int j = 0; j < size; j++) {
      matriz->arr[i][j].a = 0;
      matriz->arr[i][j].b = 0;
    }
  }

  return matriz;
}

static void matriz_destruir(Matriz matriz) {
  if (matriz == NULL) return;
  
  for (int i = 0; i < matriz->size; i++) {
    free(matriz->arr[i]);
  }

  free(matriz->arr);
  free(matriz);
}

AEF aef_crear(int size) {
  if (size == 0) return NULL;

  AEF aef = malloc(sizeof(struct _AEF));

  aef->na = calloc(size, sizeof(int));

  aef->matriz = matriz_crear(size);

  return aef;
}

void aef_destruir(AEF aef) {
  if (aef == NULL) return;

  free(aef->na);
  matriz_destruir(aef->matriz);
  free(aef);
}

static void matriz_escribir_a(Matriz matriz, int fila, int col, int a) {
  if (matriz == NULL) return;
  
  matriz->arr[fila][col].a = a;
}

static void matriz_escribir_b(Matriz matriz, int fila, int col, int b) {
  if (matriz == NULL) return;
  
  matriz->arr[fila][col].b = b;
}

static CasillaMatriz matriz_leer(Matriz matriz, int fila, int col) {
  assert(matriz != NULL);

  CasillaMatriz casilla = matriz->arr[fila][col];
  
  return casilla;
}

// Si no queremos modificar una de las transiciones la funcion debe recibir -1
void aef_agregar_transicion(AEF aef, int nodoI, int nodoF, int a, int b) {
  if (aef == NULL) return;

  if (a == -1 && b == -1) return;

  if (a == -1) matriz_escribir_b(aef->matriz, nodoI, nodoF, b);

  else if (b == -1) matriz_escribir_a(aef->matriz, nodoI, nodoF, a);

  else {
    matriz_escribir_a(aef->matriz, nodoI, nodoF, a);
    matriz_escribir_b(aef->matriz, nodoI, nodoF, b);
  }
}

AEF aef_leer_archivo(FILE* file) {
  FILE* data = file;

  int matrizSize;
  fscanf(data, "%d", &matrizSize);

  if (matrizSize <= 0) return NULL;

  AEF aef = aef_crear(matrizSize);

  char buffer[255];
  int j = 0;

  // fscanf no come el \n
  fgets(buffer, 255, data);

  for (int i = 0; i < matrizSize && fgets(buffer, 255, data) != NULL; i++) {
    j = 0;
    for (int k = 0; buffer[k] != '\0'; k++) {
      if (buffer[k] == ';') j++; 

      if (buffer[k] == 'a') matriz_escribir_a(aef->matriz, i, j, 1);

      if (buffer[k] == 'b') matriz_escribir_b(aef->matriz, i, j, 1);
    }
  }

  int naTemp;

  while(fscanf(data, "%d", &naTemp) != EOF) {
    aef->na[naTemp] = 1;
  }

  fclose(data);

  return aef;
}

void aef_imprimir(AEF aef) {
  if (aef == NULL) return;

  CasillaMatriz casilla;

  for (int i = 0; i < aef->matriz->size; i++) {
    for (int j = 0; j < aef->matriz->size; j++) {
      casilla = matriz_leer(aef->matriz, i, j);
      printf("(a: %d, b: %d) | ", casilla.a, casilla.b);
    }
    puts("");
  }
  printf("Estados de aceptacion: ");
  for (int i = 0; i < aef->matriz->size; i++) {
    if (aef->na[i] == 1) printf("%d ", i);
  }

  puts("");
}

static int aef_transiciona_con(AEF aef, int sI, int sF, char etiqueta) {
  if (aef == NULL) return 0;

  // Como en las filas ubicamos de donde sale la trasicion y en la columna
  // hacia donde va (la columna es el sucesor) hacemos la lectura de la 
  // siguiente manera
  CasillaMatriz casilla = matriz_leer(aef->matriz, sI, sF);

  if (etiqueta == 'a') return casilla.a;

  else if (etiqueta == 'b') return casilla.b;

  return 0;
}

// l indice de palabra (letra)
// s: estado
static int aef_buscar_palabra_rec(AEF aef, char* palabra, int l, int s) {
  if (palabra[l] == '\0' && aef->na[s] == 1) return 1;
  else if (palabra[l] == '\0') return 0;

  int encontrada = 0;

  for (int j = 0; j < aef->matriz->size && !encontrada; j++) {
    if (aef_transiciona_con(aef, s, j, palabra[l])) {
      encontrada = aef_buscar_palabra_rec(aef, palabra, l + 1, j);
    }
  }
  return encontrada;
}


int aef_buscar_palabra(AEF aef, char* palabra) {
  return aef_buscar_palabra_rec(aef, palabra, 0, 0);
}
