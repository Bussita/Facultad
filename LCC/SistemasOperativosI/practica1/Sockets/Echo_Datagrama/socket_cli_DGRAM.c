#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define MAXMSG 1024

#define MSG "Hola Mundo"
int main(){
    int socket_cli = socket(AF_UNIX, SOCK_DGRAM, 0);
    int cli_size;
    char buff[MAXMSG + 1];
    struct sockaddr_un srv_name, cli_name;
   
    strcpy(buff, MSG);

    srv_name.sun_family = AF_UNIX;
    strcpy(srv_name.sun_path,"SRV_NAME");

    socklen_t srv_size = sizeof(srv_name);

    cli_name.sun_family = AF_UNIX;
    strcpy(cli_name.sun_path,"CLI_NAME");

    printf("[CLI] SEND TO...\n");
    sendto(socket_cli, buff, strlen(buff), 0, (struct sockaddr *)&srv_name, srv_size);

    unlink(cli_name.sun_path);
    
    bind(socket_cli, (struct sockaddr*)&cli_name, sizeof(cli_name));
    
    printf("[CLI] RECVFROM...\n");
    
    int nbytes = recvfrom(socket_cli, buff, strlen(buff), 0,(struct sockaddr *) &srv_name, &srv_size);

    printf("[CLI] recv: %s\n",buff);

    printf("[SRV] SEND OK\n");

    close(socket_cli);

    remove("./CLI_NAME");
    return 0;
}