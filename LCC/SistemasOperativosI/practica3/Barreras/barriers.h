#ifndef __BARRIERS_H__
#define __BARRIERS_H__
#include <pthread.h>

struct barrier{
    pthread_cond_t vcond;
    int n;
    int contador;
    int fase;
};

void barrier_init(struct barrier* b, int n);

void barrier_wait(struct barrier* b);
#endif