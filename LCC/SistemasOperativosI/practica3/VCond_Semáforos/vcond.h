#ifndef __VCOND_H__
#define __VCOND_H__

#include <semaphore.h>
#include "queue.h"

typedef sem_t mutex_t;


struct VCond{
    SemQueue* q;
    mutex_t mutex;
};

void vcond_init(struct VCond*, mutex_t);

void vcond_wait(struct VCond*, mutex_t);

void vcond_signal(struct VCond*);

void vcond_broadcast(struct VCond*);

#endif