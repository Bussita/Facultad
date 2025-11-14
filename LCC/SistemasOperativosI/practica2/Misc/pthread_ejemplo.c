#include <stdio.h>
#include <pthread.h>
#include <sys/wait.h>

void* function(void* v){
    printf("thread: v: %d\n",*((int*) v));
    pthread_exit(0);
}

int main(){
    
    pthread_t id;
    int v = 2, *ptr;
    pthread_create(&id, NULL, function, &v);
    pthread_join(id,(void**) &ptr);
    printf("Main running. Thread return value: %p\n",ptr);
    return 0;
}