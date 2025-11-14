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
    int status;
    pid_t pid = fork();

    if(pid == 0){
        struct sigaction siga;
        siga.sa_flags = SA_RESTART;
        siga.sa_handler = SIG_DFL;
    }
    return 0;
}