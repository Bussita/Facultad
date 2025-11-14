#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int status;
void handler(int s){ 
    pause();
}
int main(){

    pid_t pid = fork();
    if(pid == 0){
        signal(SIGUSR1, handler);
        raise(SIGUSR1);
        printf("Hijo recibe señal \n");
    }else{
        kill(pid ,SIGUSR1);
        wait(&status);
        signal(SIGUSR1, handler);
        printf("Padre recibe señal \n");
    }
    return 0;
}
