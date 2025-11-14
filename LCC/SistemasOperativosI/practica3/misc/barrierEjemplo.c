#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>

pthread_barrier_t barrera;
void* rutina(void* v){
    printf("Soy thread %p\n",v);
    pthread_barrier_wait(&barrera);
    printf("SOY EL THREAD %p y he pasado la barrera papu.\n",v);
    return NULL;
}
int main(){

    pthread_barrier_init(&barrera, NULL, 3);
    pthread_t th[3];
    pthread_create(&th[0],NULL, rutina, (void *)1);
    pthread_create(&th[1],NULL, rutina, (void*)2);
    pthread_create(&th[2],NULL, rutina, (void*) 3);

    pthread_join(th[0],NULL);
    pthread_join(th[1],NULL);
    pthread_join(th[2],NULL);
    return 0;
}