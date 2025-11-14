#include <stdio.h>
#include <pthread.h>

#define MAXVISITANTES 100000

int contadorVisitantes = 0;
int main(){
    for(int i=0; i < MAXVISITANTES; i++) contadorVisitantes++;
    return 0;
}