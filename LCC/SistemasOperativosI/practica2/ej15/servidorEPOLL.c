#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/epoll.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

/*
 * Para probar, usar netcat. Ej:
 *
 *      $ nc localhost 4040
 *      NUEVO
 *      0
 *      NUEVO
 *      1
 *      CHAU
 */

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int epfd;

struct epoll_event ev;

void quit(char *s)
{
	perror(s); 	
	abort();
}

int U = 0; // NUmero de pedido

int fd_readline(int fd, char *buf)
{
	int rc;
	int i = 0;

	/*
	 * Leemos de a un caracter (no muy eficiente...) hasta
	 * completar una línea.
	 */
	while ((rc = read(fd, buf + i, 1)) > 0) {
		if (buf[i] == '\n')
			break;
		i++;
	}

	if (rc < 0)
		return rc;

	buf[i] = 0;
	return i;
}

void handle_conn(int csock)
{
	char buf[200];
	int rc;

	while (1) {
		/* Atendemos pedidos, uno por linea */

		rc = fd_readline(csock, buf);
		
        if (rc < 0)
			quit("read... raro");

		if (rc == 0) {
			/* linea vacia, se cerró la conexión */
			close(csock);
		}

		if (!strcmp(buf, "NUEVO")) {
            pthread_mutex_lock(&lock);
            char reply[20];
			sprintf(reply, "%d\n", U);
			U++;

            struct epoll_event nuevoEvento;
            nuevoEvento.events = EPOLLIN | EPOLLONESHOT;
            nuevoEvento.data.fd = csock;
            epoll_ctl(epfd,EPOLL_CTL_MOD,csock, &nuevoEvento);
            
            pthread_mutex_unlock(&lock);
			write(csock, reply, strlen(reply));
		} else if (!strcmp(buf, "CHAU")){
            struct epoll_event evento;
            evento.data.fd = csock;
            epoll_ctl(epfd,EPOLL_CTL_DEL,csock,&evento);
			close(csock);
		}
	}
}

void* wait_for_clients(void* lsock)
{
	int csock; // connect socket

	int serverSock = *((int*)lsock);

	struct epoll_event evento;

		while(1) {
			
			epoll_wait(epfd, &evento, 1,-1);

			
			if (evento.data.fd == serverSock) {

                int csock = accept(serverSock, NULL, NULL);

                struct epoll_event nuevoEvento;
                nuevoEvento.events = EPOLLIN | EPOLLONESHOT;
                nuevoEvento.data.fd = csock;
				// Ese nuevo FD del accept, lo agregaria al epoll al igual que lsock
				epoll_ctl(epfd,EPOLL_CTL_ADD,csock,&nuevoEvento);
				// Y dependecomo configures el evento de lsock, capaz tenes que volver
				// a agregar a lsock (EPOLL_ONE_SHOT)
                nuevoEvento.events = EPOLLIN | EPOLLONESHOT;
                nuevoEvento.data.fd = serverSock;
				epoll_ctl(epfd,EPOLL_CTL_MOD,serverSock,&nuevoEvento);
			}

			else { // Es un cliente, que nos esta mandando informacion por su socket

                handle_conn(evento.data.fd);
				// Parsear lo que me envio

				// Si termine de parsear, manejar la respuesta.
			}
		}
        pthread_exit(NULL);
}

/* Crea un socket de escucha en puerto 4040 TCP */
int mk_lsock()
{
	struct sockaddr_in sa;
	int lsock; // listen socket
	int rc;
	int yes = 1;

	/* Crear socket */
	lsock = socket(AF_INET, SOCK_STREAM, 0);
	if (lsock < 0)
		quit("socket");

	/* Setear opción reuseaddr... normalmente no es necesario */
	if (setsockopt(lsock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == 1)
		quit("setsockopt");

	sa.sin_family = AF_INET;
	sa.sin_port = htons(4040);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);

	/* Bindear al puerto 4040 TCP, en todas las direcciones disponibles */
	rc = bind(lsock, (struct sockaddr *)&sa, sizeof sa);
	if (rc < 0)
		quit("bind");

	/* Setear en modo escucha */
	rc = listen(lsock, 10);
	if (rc < 0)
		quit("listen");

	return lsock;
}

int main()
{
	int lsock;

  pthread_t threads[5];

	lsock = mk_lsock(); // Socket del server
	
    int epfd = epoll_create1(0); // Aca creas la instancia de epoll

    if (epfd == -1){
        perror("error al crear epoll\n");
        exit(EXIT_FAILURE);
    }

    ev.events = EPOLLIN | EPOLLONESHOT;
    ev.data.fd = lsock;

    epoll_ctl(epfd, EPOLL_CTL_ADD, lsock, &ev);

    for(int i =0; i<5; i++)
        pthread_create(threads + i, NULL, wait_for_clients,(void*)&lsock);
    
    for(int i=0; i<5; i++) 
        pthread_join(threads[i],NULL);
}


