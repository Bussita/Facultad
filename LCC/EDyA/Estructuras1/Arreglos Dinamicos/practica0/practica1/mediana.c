#include <stdio.h>
#include <stdlib.h>

void bubble_sort(float arreglo[], int longitud) {
    for (int iter = 0 ; iter < longitud - 1 ; iter++) {
        for (int i = 0 ; i < longitud - iter - 1; i++) {
            if (arreglo[i] > arreglo[i + 1]) {
                float aux = arreglo[i];
                arreglo[i] = arreglo[i + 1];
                arreglo[i + 1] = aux;
            }
        }
    }
}

float mediana(float *arreglo, int longitud){
    bubble_sort(arreglo, longitud);
    if(longitud % 2 != 0){
        return arreglo[longitud/2];
    }
    float promedio;
    int i;
    for(i=0;i<longitud/2;i++);
    promedio = (arreglo[i-1] + arreglo[i])/2;
    return promedio;
}

int main(){
    float arreglo[]={-1.0, 2.2,2.9,3.1}, media;
    media = mediana(arreglo, 4);
    printf("La mediana del arreglo es %f\n",media);
    return 0;
}