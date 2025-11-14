#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define M 5
#define N 5
#define SZ 8

pthread_cond_t puedoConsumir = PTHREAD_COND_INITIALIZER;
pthread_cond_t puedoProducir = PTHREAD_COND_INITIALIZER;

int in = 0, out = 0; // cola fifo

int condProductor = SZ, condConsumidor = 0;

pthread_mutex_t lock;
/*
 * El buffer guarda punteros a enteros, los
 * productores los consiguen con malloc() y los
 * consumidores los liberan con free()
 */
int *buffer[SZ];

void enviar(int *p)
{
    pthread_mutex_lock(&lock);    
    while(!condProductor) pthread_cond_wait(&puedoProducir,&lock);
    buffer[in] = p;
    in = (in + 1) % SZ;
    condProductor--;
    condConsumidor++;
    pthread_cond_signal(&puedoConsumir);
    pthread_mutex_unlock(&lock);
    return;
}

int *recibir()
{
    pthread_mutex_lock(&lock);
    while(condConsumidor ==0) pthread_cond_wait(&puedoConsumir,&lock);

    int* p = buffer[out];
    out = (out + 1) % SZ;
    condConsumidor--;
    condProductor++;
    pthread_cond_signal(&puedoProducir);
    pthread_mutex_unlock(&lock);
    return p;
}

void *prod_f(void *arg)
{
    int id = arg - (void *)0;
    while (1)
    {
        sleep(random() % 3);

        int *p = malloc(sizeof *p);
        *p = random() % 100;
        printf("Productor %d: produje %p->%d\n", id, p, *p);
        enviar(p);
    }
    return NULL;
}

void *cons_f(void *arg)
{
    int id = arg - (void *)0;
    while (1)
    {
        sleep(random() % 3);

        int *p = recibir();
        printf("Consumidor %d: obtuve %p->%d\n", id, p, *p);
        free(p);
    }
    return NULL;
}

int main()
{
    pthread_t productores[M], consumidores[N];
    int i;
    for (i = 0; i < M; i++)
        pthread_create(&productores[i], NULL, prod_f, i + (void *)0);

    for (i = 0; i < N; i++)
        pthread_create(&consumidores[i], NULL, cons_f, i + (void *)0);

    pthread_join(productores[0], NULL); /* Espera para siempre */
    return 0;
}
