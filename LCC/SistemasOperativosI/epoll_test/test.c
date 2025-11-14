#include <sys/epoll.h>
#include <stdlib.h>

int main(){
    int lista[100];
    int epfd = epoll_create(10000);
    epoll_wait(epfd,lista, 100,100);
    return 0;
}