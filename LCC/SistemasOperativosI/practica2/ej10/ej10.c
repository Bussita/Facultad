#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


int contador = 0, arr[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
int tamanio = 20, sumaTot=0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* suma(void* value){
    while(contador < tamanio){
        pthread_mutex_lock(&lock);
        if(contador<tamanio){
            sumaTot = sumaTot + arr[contador];
            contador++;
            printf("La suma actual es: %d contador %d (Thread: %p)\n",sumaTot,contador, value);
        }
        pthread_mutex_unlock(&lock);
    }
}

int main(){
    pthread_t t1, t2;
    int v=1, *retorno, v2=2;
    pthread_create(&t1,NULL,suma,(void*)&v);
    pthread_create(&t2,NULL,suma,(void*)&v2);

    pthread_join(t1,(void**)&retorno);
    pthread_join(t2,(void**)&retorno);
    
    printf("Suma total: %d\n",sumaTot);
    return 0;
}
