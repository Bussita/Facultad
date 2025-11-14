#include "ordenamiento.h"
#include <stdio.h>
#include <stdlib.h>

// Función para imprimir el arreglo
void imprimirArreglo(int* arr, int largo) {
    for (int i = 0; i < largo; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    long int* arr= malloc(sizeof(long int)* 10000000);
    printf("Arreglo desordenado: \n");
    for(long int i = 0; i<10000000; i++){
        arr[i] = rand() % 100000;
    }
    printf("Dato encontrado en el indice %ld",binsearchR(arr,0,10000000-1,100));
    //printf("\nArreglo ordenado: \n");
    //int* ordenado = malloc(sizeof(int)* 100000000);
    //ordenado = mergeSort(arr, 100000000);
    //quickSort(arr, 10000000);
    //imprimirArreglo(arr, 10000000);
    //free(ordenado);
    free(arr);
    return 0;
}
