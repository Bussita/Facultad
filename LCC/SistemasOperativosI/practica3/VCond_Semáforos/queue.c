#include <semaphore.h>
#include <stdlib.h>
#include "queue.h"

sem_t primero(sem_t[]){

}
SemQueue* queue_create(){
    SemQueue* queue = malloc(sizeof(SemQueue));
    queue->lastIndex = 0;
    queue->firstIndex = 0;
    sem_t mutex;
    sem_init(&mutex,0,1);
    queue->mutex = mutex;
    return queue;
}

sem_t queue_getFirst(SemQueue* queue){
    sem_wait(&queue->mutex);
    sem_t first = queue->queue[queue->firstIndex];
    queue->firstIndex++;
    sem_post(&queue->mutex);
    return first;   
}

SemQueue* queue_add(SemQueue* queue, sem_t semaphore){
    sem_wait(&queue->mutex);
    queue->queue[queue->lastIndex] = semaphore;
    queue->lastIndex++;
    sem_post(&queue->mutex);
    return queue;
}

void queue_destroy(SemQueue* queue){ free(queue);}

