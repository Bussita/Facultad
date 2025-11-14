  #include "bstree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Casos de prueba para arboles de busqueda binaria generales
 */

#define N_PALABRAS 16

static void *copiar_cadena(void *dato) {
  char *str = malloc(sizeof(char) * (strlen(dato) + 1));
  assert(str != NULL);
  strcpy(str, dato);
  return str;
}
static int comparar_cadena(void *dato1, void *dato2) {
  return strcmp(dato1, dato2);
}
static void destruir_cadena(void *dato) { free(dato); }
static void destruir_int(void *dato) { free(dato); }

static void imprimir_cadena(void *dato, __attribute__((unused)) void *extra) {
  /* __attribute__((unused)) le dice al compilador que esta variable puede no
   * ser usada, de esta forma las banderas no tiran warnings.*/
  printf("\"%s\" \n", (char *)dato);
}

void imprimir_int(int *dato, __attribute__((unused)) void *extra) {
  /* __attribute__((unused)) le dice al compilador que esta variable puede no
   * ser usada, de esta forma las banderas no tiran warnings.*/
  printf("%d \n", *dato);
}
static int comparar_int(int *dato1, int *dato2) {
  if(*dato1 == *dato2) return 0;
  if(*dato1 < *dato2) return -1;
  if(*dato1 > *dato2) return 1;

}

int *copiar_int(int* dato){
  int *copia = malloc(sizeof(int));
  *copia = *dato;
  return copia;
}


int main() {

  char *palabras[N_PALABRAS] = {"gato",      "perro",    "casa",     "persona",
                                "parque",    "arbol",    "edificio", "calle",
                                "argentina", "santa fe", "rosario",  "unr",
                                "edya",      "farmacia", "tiempo",   "celular"};


  int *a = malloc(sizeof(int));
  *a = 5;
  int *b = malloc(sizeof(int));
  *b = 10;
  int *c = malloc(sizeof(int));
  *c = 18;
  int *d = malloc(sizeof(int));
  *d = 2;
  int *e = malloc(sizeof(int));
  *e = 6;
  int *f = malloc(sizeof(int));
  *f = 4;
  int *g = malloc(sizeof(int));
  *g = 13;
  int *h = malloc(sizeof(int));
  *h = 19;
  int *i = malloc(sizeof(int));
  *i = 14;


  // Creamos un arbol vacio y le insertamos las palabras
  BSTree arbol = bstee_crear();
  BSTree arbol_2 = bstee_crear();
  for (int i = 0; i < N_PALABRAS; i++)
    arbol = bstree_insertar(arbol, palabras[i], copiar_cadena, comparar_cadena);
  
  arbol_2 = bstree_insertar(arbol_2, a, (FuncionCopiadora) copiar_int, (FuncionComparadora) comparar_int);
  arbol_2 = bstree_insertar(arbol_2, b, (FuncionCopiadora) copiar_int, (FuncionComparadora) comparar_int);
  arbol_2 = bstree_insertar(arbol_2, c, (FuncionCopiadora) copiar_int, (FuncionComparadora) comparar_int);
  arbol_2 = bstree_insertar(arbol_2, d, (FuncionCopiadora) copiar_int, (FuncionComparadora) comparar_int);
  arbol_2 = bstree_insertar(arbol_2, e, (FuncionCopiadora) copiar_int, (FuncionComparadora) comparar_int);
  arbol_2 = bstree_insertar(arbol_2, f, (FuncionCopiadora) copiar_int, (FuncionComparadora) comparar_int);
  arbol_2 = bstree_insertar(arbol_2, g, (FuncionCopiadora) copiar_int, (FuncionComparadora) comparar_int);
  arbol_2 = bstree_insertar(arbol_2, h, (FuncionCopiadora) copiar_int, (FuncionComparadora) comparar_int);
  arbol_2 = bstree_insertar(arbol_2, i, (FuncionCopiadora) copiar_int, (FuncionComparadora) comparar_int);

  // Imprimir el arbol inorden (alfabetico)
  printf("Recorrido inorden: \n");
  bstree_recorrer(arbol_2, BTREE_RECORRIDO_IN, (FuncionVisitanteExtra) imprimir_int, NULL);
  //bstree_recorrer(arbol, BTREE_RECORRIDO_PRE, imprimir_cadena, NULL);
  getchar();

  arbol_2 = bstree_eliminar(arbol_2, d, (FuncionComparadora)comparar_int, (FuncionDestructora) destruir_int);

  printf("Recorrido inorden: \n");

  bstree_recorrer(arbol_2, BTREE_RECORRIDO_IN, (FuncionVisitanteExtra) imprimir_int, NULL);
  getchar();



  // Buscar elementos
  /*assert(bstree_buscar(arbol, "farmacia", comparar_cadena) == 1);
  assert(bstree_buscar(arbol, "santa fe", comparar_cadena) == 1);
  assert(bstree_buscar(arbol, "persona", comparar_cadena) == 1);
  assert(bstree_buscar(arbol, "unr", comparar_cadena) == 1);
  assert(bstree_buscar(arbol, "argentina", comparar_cadena) == 1);
  assert(bstree_buscar(arbol, "telefono", comparar_cadena) == 0);
  assert(bstree_buscar(arbol, "mail", comparar_cadena) == 0);
  assert(bstree_buscar(arbol, "parques", comparar_cadena) == 0);
  assert(bstree_buscar(arbol, "EDyA1", comparar_cadena) == 0);*/

  // Destruir arbol
  //bstree_destruir(arbol, destruir_cadena);

  return 0;
}
