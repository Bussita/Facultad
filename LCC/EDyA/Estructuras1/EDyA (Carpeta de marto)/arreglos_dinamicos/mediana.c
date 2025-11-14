#include <stdio.h>
#include <stdlib.h>

float mediana(float *arreglo, int longitud);

void bubble_sort(float *arreglo, int longitud);

void copiar_arreglo(float *arreglo1, float *arreglo2, int longitud);

int main(void) {

    float arreglo1[5] = {-1.0, 2.2, 2.9, 3.1, 3.5}; 
    float arreglo2[4] = {-1.0, 2.2, 2.9, 3.1}; 

    printf("Mediana arreglo 1: %.2f\n",mediana(arreglo1, 5));
    printf("Mediana arreglo 2: %.2f\n",mediana(arreglo2, 4));



    return 0;
}

float mediana(float *arreglo, int longitud){

    float copia_arreglo[longitud];

    copiar_arreglo(copia_arreglo, arreglo, longitud);

    bubble_sort(copia_arreglo, longitud);

    if (longitud % 2 != 0) 

        return arreglo[(longitud - 1) / 2];        

    return (arreglo[longitud / 2] + arreglo[longitud / 2 - 1]) / 2;
}



void bubble_sort(float *arreglo, int longitud){

    for (int iter = 0 ; iter < longitud - 1 ; iter++) {

        for (int i = 0 ; i < longitud ; i++) {

            if (arreglo[i] > arreglo [i + 1]) {

                float aux = arreglo[i];
                arreglo[i] = arreglo[i + 1];
                arreglo[i + 1] = aux;
            }
        }
    }
}


void copiar_arreglo(float *arreglo1, float *arreglo2, int longitud) {

    for (int i = 0 ; i < longitud ; i++) 

        arreglo1[i] = arreglo2[i];

}

