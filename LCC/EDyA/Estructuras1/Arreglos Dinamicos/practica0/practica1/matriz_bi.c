#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

float** crear_matriz(int tamanio1, int tamanio2){
    float** Matriz = malloc(sizeof(float*)*tamanio1);
    for(int i=0; i<tamanio2;i++){
        Matriz[i] = malloc(sizeof(float*));
    }
    return Matriz;
}

void destruir_matriz(float** matriz, int tamanio2){
    for(int i =0; i<tamanio2; i++){
        free(matriz[i]);
    }
    free(matriz);
}
void escribir_matriz(float** matriz, int i, int j, int dato){
    matriz[i-1][j-1] = dato;
}
void leer_matriz(float** matriz, int i, int j){
    printf("El elemento en la posicion dada es %f\n",matriz[i-1][j-1]);    
}
int main(){
    return 0;
}