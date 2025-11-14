#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <math.h>
#include <stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


double suma = 0;

double* arreglo;

void* rutina(void* v){
    int n = 5 * pow(10,8);
    for(int i = 0; i < n; i++){
        pthread_mutex_lock(&mutex);
        suma += arreglo[i];
        pthread_mutex_unlock(&mutex);
    }
    return v;
}

int main(){
    int n = 5 * pow(10,8);
    arreglo = malloc(sizeof(double)*n);

    pthread_t th[8];
    for(int i=0; i<8; i++){
        pthread_create(&th[i],NULL,rutina,NULL);
    }
    for(int i=0; i < n; i++){
        arreglo[i] = 1;
    }
    pthread_join(th[0],NULL);
    printf("La suma del arreglo es %f\n",suma);
    return 0;
}

// La implementacion secuencial dura 3 minutos 36,476 segundos.