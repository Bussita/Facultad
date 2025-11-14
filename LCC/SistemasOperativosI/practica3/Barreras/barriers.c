#include "barriers.h"
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void barrier_init(struct barrier* b, int n){
    b->contador = b->n = n;
    b->fase = 0;
    pthread_cond_init(&b->vcond,NULL);
}

void barrier_wait(struct barrier* b) {
    pthread_mutex_lock(&lock);
    int mi_fase = b->fase;

    b->contador--;
    if (b->contador == 0) {
        b->fase++;  // avanza a la siguiente generación
        b->contador = b->n;
        pthread_cond_broadcast(&b->vcond);
    } else {
        while (mi_fase == b->fase) {
            pthread_cond_wait(&b->vcond, &lock);
        }
    }

    pthread_mutex_unlock(&lock);
}