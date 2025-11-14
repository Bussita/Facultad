#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#define MAXVISITANTES 100000

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int contVisitantes = 0;

void* molinete1(void* value){
    for(int i=0; i<MAXVISITANTES/2; i++){
        pthread_mutex_lock(&mutex); 
        contVisitantes++;
        pthread_mutex_unlock(&mutex);
    }
    return value;
}

void* molinete2(void* value){
    for(int i=0; i<MAXVISITANTES/2; i++){
        pthread_mutex_lock(&mutex); 
        contVisitantes++;
        pthread_mutex_unlock(&mutex);
    }
    return value;
}

int main(){
    pthread_t m1, m2;
    int v=3, *result;

    pthread_create(&m1, NULL, molinete1, (void*)&v);
    pthread_create(&m2, NULL, molinete2, (void*)&v);

    pthread_join(m1,(void**)&result);
    pthread_join(m2,(void**)&result);

    return 0;
}