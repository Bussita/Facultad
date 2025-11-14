#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define MAXMSG 1024
#define SERVER_NAME "./SERVER_NAME"
int main(){
    struct sockaddr_un srv_name, cli_name;
    socklen_t srv_size, cli_size;
    
    char buff[MAXMSG + 1];
    ssize_t nbytes;

    int socket_srv = socket(AF_UNIX, SOCK_STREAM, 0);
    printf("[SRV] SOCKET OK.\n");
    srv_name.sun_family = AF_UNIX;
    strcpy(srv_name.sun_path, SERVER_NAME);
    if(bind(socket_srv, (struct sockaddr*) &srv_name, sizeof(srv_name.sun_path))){
        perror("Fallo la asignacion del nombre del servidor.\n");
        exit(EXIT_FAILURE);
    }

    listen(socket_srv, 1);

    int socket_cli = accept(socket_srv, (struct sockaddr*)&cli_name, &cli_size);
    nbytes = recv(socket_cli, buff, MAXMSG, 0);

    buff[nbytes] = '\0';
    printf("[SRV]: MENSAJE RECIBIDO: %s\n",buff);
    send(socket_cli, buff, nbytes, 0);

    close(socket_cli);
    close(socket_srv);

    remove(SERVER_NAME);
    return 0;
}