#include <stdio.h>
#include <stdlib.h>
#include "arregloenteros.h"

ArregloEnteros* arreglo_enteros_crear(int capacidad){
    ArregloEnteros* arreglo = malloc(sizeof(ArregloEnteros));
    if(arreglo == NULL){
        printf("No hay memoria.");
        exit(1);
    }
    arreglo->direccion = malloc(sizeof(int)*capacidad);
    arreglo->capacidad = capacidad;
    return arreglo;
}

void arreglo_enteros_destruir(ArregloEnteros* arreglo){
    free(arreglo->direccion);
    free(arreglo);
}

int arreglo_enteros_leer(ArregloEnteros* arreglo, int pos){
    printf("El caracter en la posicion %d del arreglo es %d\n",pos,arreglo->direccion[pos]);
    return arreglo->direccion[pos];
}

void arreglo_enteros_escribir(ArregloEnteros* arreglo, int pos, int dato){
    arreglo->direccion[pos] = dato;
}

int arreglo_enteros_capacidad(ArregloEnteros* arreglo){
    return arreglo->capacidad;
}

void arreglo_enteros_imprimir(ArregloEnteros* arreglo){
    for(int i=0; i<arreglo->capacidad; i++){
        printf("%d ",arreglo->direccion[i]);
    }
    printf("\n");
}

void arreglo_enteros_ajustar(ArregloEnteros* arreglo, int capacidadNueva){
    arreglo->direccion =  realloc(arreglo->direccion, capacidadNueva);
    arreglo->capacidad = capacidadNueva;
    return;
}

void arreglo_enteros_insertar(ArregloEnteros* arreglo, int pos, int dato){
    if(arreglo == NULL){
        return;
    }
    printf("capacidad es %d \n",arreglo->capacidad);
    arreglo->direccion = realloc(arreglo->direccion,arreglo->capacidad++);
    printf("capacidad es %d \n",arreglo->capacidad);
    int aux=arreglo->direccion[pos], aux2;
    arreglo->direccion[pos] = dato;
    for(int i=pos+1; i<arreglo->capacidad;i++){
        aux2 = arreglo->direccion[i];
        arreglo->direccion[i] = aux;
        aux = aux2;
    }
    return;
}

void arreglo_enteros_eliminar(ArregloEnteros* arreglo, int pos){
    for(int i=pos;i<arreglo->capacidad-1;i++){
        arreglo->direccion[i] = arreglo->direccion[i+1];
    }
    arreglo->direccion = realloc(arreglo->direccion, arreglo->capacidad--);
    return;
}
int main(){
    ArregloEnteros* arreglo = arreglo_enteros_crear(5);
    for(int i=0; i<5;i++){
        arreglo->direccion[i]= i;
    }
    arreglo_enteros_imprimir(arreglo);
    arreglo_enteros_eliminar(arreglo, 2);
    arreglo_enteros_imprimir(arreglo);

    arreglo_enteros_destruir(arreglo);
    return 0;
}