#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>

double* arreglo;

double suma = 0;

int main(){

    int n = 5*pow(10,8);
    arreglo = malloc(sizeof(double)*n);
    printf("Inicializando arreglo.\n");
    #pragma omp parallel
    {
        #pragma omp for
        for(int i = 0; i < n; i++){
            arreglo[i] = i;
        }
    }
    printf("Arreglo inicializado.\n");
    #pragma omp parallel
    {
        #pragma omp for reduction(+: suma)
        for(int i = 0; i < n; i++){
            suma += arreglo[i];

        }
    }
    printf("La suma del arreglo es %f\n",suma);
    return 0;
}

/* La versión paralela sin mutex dura unos 5,2 segundos.
Sin embargo pierde mucha informacion al haber race condition
en cada procesador.

La version paralela con mutex dura 46,774 segundos,
el cual realiza la suma correctamente pero perdemos
mucho tiempo.

La version paralela con reduction suma dura 56,274 segundos.
*/