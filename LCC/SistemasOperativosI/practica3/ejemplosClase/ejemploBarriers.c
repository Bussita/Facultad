#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>

pthread_barrier_t barrier;

void* thread_fun(void* v){
    printf("Thread %ld antes de la barrera\n", (long) v);
    pthread_barrier_wait(&barrier);
    printf("Thread %ld despues de la barrera\n", (long) v);

}

int main(){
    
    pthread_barrier_init(&barrier, NULL, 3);
    pthread_t threads[3];

    for(int i=0;i<3; i++){
        pthread_create(threads + i, NULL, thread_fun, (void *) i);
    }
    for(int i=0;i<3; i++){
        pthread_join(threads[i], NULL);
    }
    return 0;
}