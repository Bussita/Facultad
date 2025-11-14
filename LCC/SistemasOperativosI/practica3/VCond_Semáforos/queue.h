#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <semaphore.h>

#define MAXTHREADS 1<<10

typedef struct SemQueue_{
    sem_t queue[MAXTHREADS];
    int lastIndex;
    int firstIndex;
    sem_t mutex;
} SemQueue;

SemQueue* queue_create();

sem_t queue_getFirst(SemQueue*);

SemQueue* queue_add(SemQueue*, sem_t);

void queue_destroy(SemQueue*);
#endif