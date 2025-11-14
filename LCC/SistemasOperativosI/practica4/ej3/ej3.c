#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>

double* arreglo;

double maximo;

int main(){

    int n = 5*pow(10,8);
    arreglo = malloc(sizeof(double)*n);
    printf("Inicializando arreglo.\n");
    #pragma omp parallel
    {
        #pragma omp for
        for(int i = 0; i < n; i++){
            arreglo[i] = rand();
        }
    }
    maximo = arreglo[0];
    printf("Arreglo inicializado.\n");
    #pragma omp parallel
    {
        #pragma omp for
        for(int i = 1; i < n; i++){
            if(arreglo[i]>= maximo){
                #pragma omp critical
                {
                    maximo = arreglo[i];
                }
            }
        }
    }
    printf("El minimo del arreglo es %f\n",maximo);
    return 0;
}