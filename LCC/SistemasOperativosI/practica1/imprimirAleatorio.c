#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/wait.h>


void printear_lista(int* lista, int n){
    for(int j=0; j<n; j++)
        if(lista[j]) printf("%d ",lista[j]);
    printf("\n");
}

int existeEnLista(int* listaDe3, int numero){
    for(int i=0; i<3; i++){
        if(listaDe3[i] == numero)
            return 1;
    }
    return 0;
}

void cargaListaDe3(int* listaHijo, int* listaDe3, int n){
    int aleatorio;
    for(int i=0; i<3; i++){
        aleatorio = (rand() % n) + 1;
        if(!existeEnLista(listaDe3,aleatorio) && listaHijo [aleatorio-1]){
            listaDe3[i] = aleatorio;
        }else{
            i--;
        }
    }
}

void actualiza_lista(int* lista, int* arrayDe3){
    for(int i = 0; i<3; i++)
        if(arrayDe3[i]) lista[arrayDe3[i]-1] = 0;  
}

void start(int* lista, int n){
    int fdPadreEscribe[2], fdHijoEscribe[2], status;
    int a = pipe(fdPadreEscribe);
    int b = pipe(fdHijoEscribe);
    if (a == -1 || b == -1){
        perror("Error al crear el pipe.");
        exit(1);
    }

    int itActual=0, maxIteraciones=(n+2)/3;
    printf("\nMaxIteraciones %d\n",maxIteraciones);
    while(itActual < maxIteraciones){
        printf("Iteracion actual %d\n",itActual);
        pid_t pid = fork();

        if(pid == 0){
            close(fdPadreEscribe[1]);
            close(fdHijoEscribe[0]);
            int listaHijo[n], listaDe3[3] = {0,0,0};
            read(fdPadreEscribe[0],listaHijo, sizeof(listaHijo));
            cargaListaDe3(listaHijo, listaDe3, n);
            printear_lista(listaDe3, 3);
            write(fdHijoEscribe[1], listaDe3, sizeof(int)*3);
            exit(0);
        }else{
            int arrayDe3[3]; 
            close(fdPadreEscribe[0]);
            close(fdHijoEscribe[1]);
            write(fdPadreEscribe[1],lista,sizeof(int) * n);
            read(fdHijoEscribe[0],arrayDe3, 3*sizeof(int));
            actualiza_lista(lista, arrayDe3);
            itActual++;
        }
    }
}
int main(){
    int n;
    printf("Ingrese un número por teclado: ");
    scanf("%d",&n);
    if (n < 3){
        perror("[ERROR] Numero Invalido.\n");
        exit(1);
    }
    int lista[n];
    for(int i=0; i<n;i++)
        lista[i] = i+1;
    
    start(lista,n);
    return 0;
}