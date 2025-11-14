#include <stdio.h>
#include <stdlib.h>

typedef void (*VisitorFunc)(int);
int sucesor(int n){
    return n+1;
}

void imprimir(int n){
    printf("%d \n",n);
}
void apply_in(int (*funcion)(int), int* n){
    *n = funcion(*n);
}

void recorre(VisitorFunc f, int arreglo[], int n){
    for(int i=0; i<n; i++){
        f(arreglo[i]);
    }
}
int main (){
    return 0;
}