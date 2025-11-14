#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define MAXSILLAS 5

sem_t clientes, barber, barberoListo, clienteListo;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int cantClientes = 0;

void me_cortan()
{
    printf("Cliente: ME ESTAN CORTANDO EL PELO :3 \n");
    sleep(2);
}

void cortando()
{
    printf("Barbero: Estoy cortando a un cliente.\n");
    sleep(2);
}

void pagando()
{
    printf("Cliente: Estoy pagando al barbero.\n");
    sleep(2);
}

void me_pagan()
{
    printf("Barbero: Recibiendo pago... Pago recibido.\n");
    sleep(2);
}

void *barbero(void *v)
{
    while (1)
    {
        pthread_mutex_lock(&lock);
        if(cantClientes == 0){
            printf("Barbero: ZzZzzZz...\n");
        }
        pthread_mutex_unlock(&lock);
        sem_wait(&clientes);
        sem_post(&barber);

        cortando();

        sem_post(&barberoListo);
        sem_wait(&clienteListo);

        me_pagan();
    }
}

void *cliente(void *v)
{
    pthread_mutex_lock(&lock);
    if (cantClientes == MAXSILLAS){
        printf("Cliente: Ocupado, me voy.\n");
        pthread_mutex_unlock(&lock);
    }else{
        if (cantClientes == 0)
        {
            printf("Cliente: Despertar al barbero...\n");
        }

        cantClientes++;
        pthread_mutex_unlock(&lock);

        sem_post(&clientes);
        sem_wait(&barber);
5
        me_cortan();

        sem_wait(&barberoListo);

        pagando();
        sem_post(&clienteListo);

        pthread_mutex_lock(&lock);
        cantClientes--;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main()
{
    sem_init(&barber, 0, 0);
    sem_init(&clientes, 0, 0);
    sem_init(&barberoListo, 0, 0);
    sem_init(&clienteListo, 0, 0);

    pthread_t barb, cli[60];

    pthread_create(&barb, NULL, barbero, NULL);
    for (int i = 0; i < 10; i++)
        pthread_create(&cli[i], NULL, cliente, NULL);


    for(int i=0; i<10;i++)
        pthread_join(cli[i],NULL);

    pthread_join(barb,NULL);
    return 0;
}
