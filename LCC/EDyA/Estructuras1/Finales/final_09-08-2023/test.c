#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

int main() {

  FILE* file = fopen("./subcadena_aa_o_bb.txt", "r");

  AEF aef = aef_leer_archivo(file);

  aef_imprimir(aef);
  
  char palabra[] = "abaab";

  printf("\nSe encuentra la palabra %s ?: %d\n", 
         palabra, aef_buscar_palabra(aef, palabra));

  aef_destruir(aef);

  printf("\n------------------------------------\n");

  FILE* file2 = fopen("./maximo_bb_no_termina_en_a.txt", "r");

  AEF aef2 = aef_leer_archivo(file2);

  aef_imprimir(aef2);

  char palabra2[] = "abba";

  printf("\nSe encuentra la palabra2 %s ?: %d\n", 
      palabra2, aef_buscar_palabra(aef2, palabra2));

  aef_destruir(aef2);

  printf("\n------------------------------------\n");

  FILE* file3 = fopen("./impar_b_par_a.txt", "r");

  AEF aef3 = aef_leer_archivo(file3);

  aef_imprimir(aef3);

  char palabra3[] = "abab";

  printf("\nSe encuentra la palabra3 %s ?: %d\n", 
      palabra3, aef_buscar_palabra(aef3, palabra3));

  aef_destruir(aef3);
  
  return 0;
}
