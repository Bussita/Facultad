#include <semaphore.h>
#include "vcond.h"
#include <stdlib.h>
#include "queue.h"

void vcond_init(struct VCond* cv, mutex_t mutex){
    cv->q = queue_create();
    cv->mutex = mutex;
}

void vcond_wait(struct VCond* cv, mutex_t mutex){
    sem_post(&mutex);

    sem_t* nuevo = malloc(sizeof(sem_t));
    sem_init(nuevo,0,0);

    cv->q = queue_add(cv->q,*nuevo);

    sem_wait(&cv->q->queue[cv->q->lastIndex]);

    sem_wait(&mutex);
}

void vcond_signal(struct VCond* cv){
    sem_t primero = queue_getFirst(cv->q);
    sem_post(&primero);
}

void vcond_broadcast(struct VCond* cv){
    for(int i = cv->q->firstIndex; i<cv->q->lastIndex; i++){
        sem_t semaforo = queue_getFirst(cv->q);
        sem_post(&semaforo);
    }
}
