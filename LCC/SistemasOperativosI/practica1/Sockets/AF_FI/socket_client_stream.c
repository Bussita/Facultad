#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


#define MAXMSG 1024
#define CLIENT_NAME "./CLIENTE"
#define MSG "PEPE"
#define SERVER_NAME "./SERVER_NAME"
int main(){
    struct sockaddr_un srv_name, cli_name;
    socklen_t srv_size, cli_size;
    
    char buff[MAXMSG + 1];
    ssize_t nbytes;

    int socket_cli = socket(AF_UNIX, SOCK_STREAM, 0);
    if(socket_cli < 0){
        perror("Fallo la asignacion del nombre del servidor.\n");
        exit(EXIT_FAILURE);
    }
    printf("[SRV] SOCKET OK.\n");

    cli_name.sun_family = AF_UNIX;
    strcpy(cli_name.sun_path, CLIENT_NAME);

    bind(socket_cli, (struct sockaddr*) &cli_name, sizeof(cli_name.sun_path));


    srv_name.sun_family = AF_UNIX;
    strcpy(srv_name.sun_path, SERVER_NAME);

    srv_size = sizeof(srv_name);

    connect(socket_cli, (struct sockaddr*) &srv_name, srv_size);


    printf("[CLI]: Conexion con %s ok.\n",SERVER_NAME);
    send(socket_cli, MSG, strlen(MSG), 0);


    recv(socket_cli, buff, MAXMSG, 0);
    
    close(socket_cli);

    return 0;
}