#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>

#define MAX_VISITANTES 4000000

int contadorVisitantes = 0;
int turno, arr[2];

void* molinete1(void* value){

    for(int i = 0; i<MAX_VISITANTES/2; i++){
        turno=1; // cedo mi turno
        arr[0] = 1; // quiero ingresar
        __asm__ __volatile__("mfence" ::: "memory");
        while(arr[1]==1 && turno != 0); // bloqueo cuando no es mi turno y el otro tiene intenciones de acceder a RC
        
        contadorVisitantes++;
                
        arr[0] = 0; // no quiero usar la RC
    }
    return value;
}

void* molinete2(void* value){

    for(int i = 0; i<MAX_VISITANTES/2; i++){
        turno = 0;
        arr[1] = 1;
        __asm__ __volatile__("mfence" ::: "memory");
        while(arr[0]==1 && turno!=1); //lock
            
        contadorVisitantes++;

        arr[1] = 0; // unlock
    }
    return value;
}

int main(){
    pthread_t m1, m2;
    int v=3, *result;
    pthread_create(&m1, NULL, molinete1,&v);
    pthread_create(&m2, NULL, molinete2,&v);
    printf("Threads creados.\n");
    pthread_join(m1,(void*)&result);
    pthread_join(m2,(void*)&result);
    printf("Numero total de visitantes: %d\n",contadorVisitantes);
    return 0;
}