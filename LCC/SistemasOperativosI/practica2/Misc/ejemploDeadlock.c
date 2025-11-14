#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <wait.h>

int test = 0;

pthread_mutex_t a = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t b = PTHREAD_MUTEX_INITIALIZER;

void* routine1(void* value){
    pthread_mutex_lock(&a);
    pthread_mutex_lock(&b);
    test++;
    pthread_mutex_lock(&b);
    pthread_mutex_lock(&a);

}

void* routine2(void* value){
    pthread_mutex_lock(&b);
    pthread_mutex_lock(&a);
    test++;
    pthread_mutex_lock(&a);
    pthread_mutex_lock(&b);

}
int main(){
    pthread_t t1,t2;
    int v=5, *result;
    pthread_create(&t1,NULL, routine1, (void*)&v);
    pthread_create(&t2,NULL, routine2, (void*)&v);

    pthread_join(t1, (void**)&result);
    pthread_join(t2, (void**)&result);

    return 0;
}