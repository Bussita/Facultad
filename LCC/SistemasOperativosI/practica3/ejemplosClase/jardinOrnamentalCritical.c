#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <omp.h>


#define MAXVISITANTES 100000

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int contVisitantes = 0;

void molinete1(void){
    #pragma parallel for
    for(int i=0; i<MAXVISITANTES/2; i++){
        #pragma omp atomic
        contVisitantes++;
    }
}

int main(){
    int numthreads = 2;
    int v=3, *result;

    #pragma omp parallel num_threads(numthreads)
    {
        molinete1();
    }
    printf("Total de visitantes: %d\n",contVisitantes);
    return 0;
}