#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

#define N 1000

int visitantes = 0;
void * proc(void *arg) {
    int i;
    int id = arg - (void*)0;
    for (i = 0; i < N/2; i++) {
        int c;
        c = visitantes;
        sleep(0.1);
        visitantes = c + 1;
    }
    return NULL;
}

int main(){
    
    pthread_t m1, m2;
    int v=3, *result;
    pthread_create(&m1, NULL, proc,&v);
    pthread_create(&m2, NULL, proc,&v);
    printf("Threads creados.\n");
    pthread_join(m1,(void*)&result);
    pthread_join(m2,(void*)&result);
    printf("Numero total de visitantes: %d\n",visitantes);

    return 0;
}