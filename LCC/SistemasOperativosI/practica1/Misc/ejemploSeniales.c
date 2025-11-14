#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

void handle_signals(int sig){
    if(sig == SIGQUIT)
        printf("Se acciono SIGQUIT.\n");
    if(sig == SIGINT){
        printf("Se acciono SIGINT. La proxima se saldra.\n");
        signal(SIGINT, SIG_DFL);
    }

}
int main(){
    signal(SIGQUIT, handle_signals);
    signal(SIGINT, handle_signals);
    
    while(1){
        
    }
    return 0;
}