#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define KBLU  "\x1B[34m"
#define KGRN  "\x1B[32m"
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"


#define MAXMSG 1000

void wait_for_input();


void redireccionamiento(char* arg[], int j){
    int i=0, status;
    char* argumentos[MAXMSG];
    while(i<j){
        argumentos[i] = arg[i];
        i++;
    }
    int pid = fork();
    if (pid == 0){
        char file[MAXMSG];
        strcpy(file,arg[j+1]);
        int fd = open(file,O_CREAT | O_WRONLY | O_TRUNC , 0644), i=0;
        int dupStandar = dup(1);
        dup2(fd, 1);
        close(dupStandar);
        execvp(arg[0],argumentos);
        exit(0);
    }else{
        wait(&status);
    }
}
void handleCommand(char* buffer){
    char* comando = strtok(buffer, " ");
    char* argumentos[MAXMSG];
    int i = 0, status, j=-1, z = -1;
    argumentos[i] = comando;
    i++;
    while((argumentos[i]=strtok(NULL, " "))!=NULL){
        if(!strcmp(argumentos[i], ">")) j = i;
        i++;
    }
    if (j != -1) {
        if (argumentos[j+1] == NULL) {
            printf(KRED "Error: falta el nombre del archivo después de '>'\n");
            return;
        }
        redireccionamiento(argumentos, j);
        return;
    }
    pid_t pid = fork();
    if (pid == 0){
        int valor = execvp(comando, argumentos);
        if(valor == -1) printf(KRED "Comando no encontrado! Intente nuevamente.\n");
        exit(0);
    }else{
        wait(&status);
    }
}
void wait_for_input(){
    char buffer[MAXMSG];
    while(1){
        printf(KGRN "> ");
        printf(KNRM);
        fgets(buffer, MAXMSG, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        if(strcmp("q",buffer)==0 || strcmp("Quit",buffer)==0 || strcmp("quit",buffer)==0 || strcmp("exit",buffer)==0 || strcmp("Exit",buffer)==0){
            break;
        }
        handleCommand(buffer);
    }
}
int main(){
    printf("%sBienvenido a Shell! Pulse q (Quit, quit) o exit para salir\n",KBLU);
    wait_for_input();

    return 0;
}