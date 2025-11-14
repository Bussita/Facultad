#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define MAXMSG 1024
int main(){
    int socket_srv = socket(AF_UNIX, SOCK_DGRAM, 0);
    int cli_size;
    char buff[MAXMSG + 1];
    struct sockaddr_un srv_name, cli_name;
    srv_name.sun_family = AF_UNIX;
    strcpy(srv_name.sun_path,"SRV_NAME");
    
    unlink(srv_name.sun_path);

    bind(socket_srv, (struct sockaddr*)&srv_name, sizeof(srv_name));
    
    int nbytes = recvfrom(socket_srv, buff, MAXMSG, 0, (struct sockaddr*)&cli_name, &cli_size);

    printf("[SRV] recv: %s\n",buff);
    sendto(socket_srv, buff, strlen(buff), 0, (struct sockaddr *)&cli_name, cli_size);

    printf("[SRV] SEND OK\n");

    close(socket_srv);

    remove("./SRV_NAME");
    return 0;
}