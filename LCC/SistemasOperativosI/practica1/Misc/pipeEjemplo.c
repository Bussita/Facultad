#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

int main(){
    int fd[2];
    int status;
    pipe(fd);
    while(1){
        pid_t pid = fork();
        if(pid == 0){
            char buffer[255];
            close(fd[1]);
            read(fd[0], buffer, 255);
            printf("Lee: %s\n", buffer);
            close(fd[0]);
            exit(0);
        }else{
            char buffer[]="Hola";
            close(fd[0]);
            write(fd[1], buffer, 5);
            close(fd[1]);
            wait(&status);
        }
    sleep(1);
    }
}