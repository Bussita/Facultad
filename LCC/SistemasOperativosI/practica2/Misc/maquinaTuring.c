#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char seek_read(int fd, off_t pos){
    char resC;

    lseek(fd,pos, SEEK_SET); // La posición es absoluta debido a la bandera.
    
    int res = read(fd,&resC, 1);
    if(res<=0) perror("No se ha podido leer en dicha posición\n");

    return resC;
}

char seek_write(int fd, off_t pos, const char c){
    
    lseek(fd, pos, SEEK_SET); // POS ABSOLUTA
    write(fd,&c,1);
}
int main(){

    int fd = open("./a.txt", O_RDWR);

    pid_t pid = fork();

    if (pid == 0){
        char c = seek_read(fd,13);
        printf("El caracter leido por child es %c\n",c);
        seek_write(fd, 13, 'A');
    }else{
        char c = seek_read(fd,13);
        printf("El caracter leido por PARENT es %c\n",c);
        seek_write(fd, 13, 'B');
    }
    close(fd);
    return 0;
}