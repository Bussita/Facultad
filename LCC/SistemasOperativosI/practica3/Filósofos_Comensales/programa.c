#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>

#define N_FILOSOFOS 5
#define ESPERA 5000000

sem_t filosofos_comiendo;

pthread_mutex_t tenedor[N_FILOSOFOS];

pthread_mutex_t * izq(int i) { return &tenedor[i]; }

pthread_mutex_t * der(int i) { return &tenedor[(i+1) % N_FILOSOFOS]; }

void pensar(int i){
    printf("Filosofo %d pensando...\n", i);
    usleep(random() % ESPERA);
}

void comer(int i){
    printf("Filosofo %d comiendo...\n", i);
    usleep(random() % ESPERA);
}

void tomar_tenedores(int i){
    pthread_mutex_lock(der(i));
    pthread_mutex_lock(izq(i));
}

void tomar_tenedores_zurdo(int i){
    pthread_mutex_lock(izq(i));
    sleep(1);
    pthread_mutex_lock(der(i));
}

void dejar_tenedores(int i){
    pthread_mutex_unlock(der(i));
    pthread_mutex_unlock(izq(i));
}

void * filosofo(void *arg){
    int i = arg - (void*)0;
    while (1){
        sem_wait(&filosofos_comiendo);
        tomar_tenedores(i);
        comer(i);
        dejar_tenedores(i);
        sem_post(&filosofos_comiendo);
        pensar(i);
    }
}

int main(){
    pthread_t filo[N_FILOSOFOS];
    int i;
    sem_init(&filosofos_comiendo,0,N_FILOSOFOS-1);
    for (i = 0; i < N_FILOSOFOS; i++)
        pthread_mutex_init(&tenedor[i], NULL);
    
    for (i = 0; i < N_FILOSOFOS; i++)
        pthread_create(&filo[i], NULL, filosofo, i + (void*)0);
    
    pthread_join(filo[0], NULL);
    sem_destroy(&filosofos_comiendo);
    return 0;   
}

/* a) Puede ocurrir deadlock si se cambia de contexto cada vez que se toma el tenedor de la derecha, por ejemplo podemos forzar el deadlock
con la linea sleep(1) entre la toma de tenedores. Entonces otro filósofo pasará a tomar la derecha y así sucesivamente,
donde cada uno termina con un solo tenedor en la mano en espera de tomar el tenedor de su izquierda*/

/* b) La espera circular se rompe al haber un zurdo. Ya que si no tiene tenedores o tiene ambos tenedores no hay deadlock (ya que solo ocurre
deadlock cuando todos los comensales tienen UN solo tenedor en la mano, y por lo tanto como hay la misma cantidad de tenedores que comensales
entonces algun comensal tiene dos tenedores y los procesos pueden avanzar).

Y si el filósofo zurdo toma el lock del tenedor a su izquieda, es imposible que haya una secuencia en la que todos los demás quedan
con un tenedor en la mano. Ya que el filósofo a su derecha va a tomar primero el tenedor de SU derecha y si toma el de su izquierda (el
que le falta al filósofo zurdo), entonces tiene dos tenedores y está comiendo. Si el filósofo a su derecha no toma dicho tenedor, entonces
queda libre para que lo tome el filósofo zurdo. Por lo que no hay posibilidad de deadlock porque ese tenedor no produce que ese par de
comensales se bloquee.

c) Si n-1 de ellos a la vez pueden intentar comer, entonces siempre hay algún filósofo con 2 tenedores en la mano (comiendo) y por lo tanto
no puede haber deadlock.

En efecto, si hay que repartir N tenedores entre n-1 comensales entonces hay al menos un comensal con 2 tenedores (teorema del palomar).
Como siempre hay un comensal que no intenta comer, entonces su tenedor a la derecha está libre para el comensal a su derecha.
Entonces el comensal de la derecha podrá agarrar el tenedor libre, y así evitando el deadlock.

*/

/*

*/