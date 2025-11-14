// PROBLEMA: Dadas dos cadenas S y W, determinar si W es subcadena de S

#include <stdio.h>
#include <string.h>

int KMP(char* S, char* W);

void completar_tabla_coincidencias(int tabla[], int n);

int main(void) {



  return 0;
}


int KMP(char* S, char* W) {

  int largo_s = strlen(S);
  int largo_w = strlen(W);
  
  int coincidencias = 0;

  int verificador = 0;

  // Ver como hacer tabla de coincidencias  
  int tabla_coincidencias[largo_w];
  completar_tabla_coincidencias(tabla_coincidencias,largo_w);


  for (int i = 0 ; i < largo_s - largo_w && verificador == 0 ; i++) {

    while (coincidencias != 0 && S[i] != W[coincidencias])

      coincidencias = tabla_coincidencias[coincidencias];


    if (S[i] == W[coincidencias])
      coincidencias += 1;

    // Si llegamos a recorrer toda la palabra W, es que encontramos una subcadena
    if (coincidencias == largo_w) 
      verificador = 1;
  }

  return verificador;
}


void completar_tabla_coincidencias(int tabla[], int n) {


}