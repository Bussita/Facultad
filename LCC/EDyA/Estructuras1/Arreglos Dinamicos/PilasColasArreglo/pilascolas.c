#include <stdio.h>
#include <stdlib.h>
#include "arregloenteros.h"

struct _Pila {
    ArregloEnteros* arr;
    int ultimo;
};

typedef struct _Pila* Pila;

Pila pila_crear(int capacidad){
    Pila nuevaPila = malloc(sizeof(struct _Pila));
    if(capacidad == 0){
        nuevaPila->arr = NULL;
        nuevaPila->ultimo = -1;
        return nuevaPila;
    }
    nuevaPila->arr = arreglo_enteros_crear(capacidad);
    nuevaPila->ultimo = 0;
    return nuevaPila;
}

void pila_destruir(Pila pila){
    arreglo_enteros_destruir(pila->arr);
    free(pila);
}

int pila_es_vacia(Pila pila){
    return (pila->ultimo == -1);
}

int pila_tope(Pila pila){
    return arreglo_enteros_leer(pila->arr, pila->ultimo);
}

void pila_apilar(Pila pila, int dato){
    if(pila->ultimo == (pila->arr->capacidad) - 1){
        arreglo_enteros_ajustar(pila->arr, 2 * pila->arr->capacidad);
    }
    pila->ultimo += 1;
    arreglo_enteros_escribir(pila->arr, pila->ultimo, dato);
}

void pila_desapilar(Pila pila){
    if(pila->ultimo>=0){pila->ultimo = pila->ultimo - 1;}
}

void pila_imprimir(Pila pila){
    for(int i=0; i<=pila->ultimo; i++){
        printf("%d ",pila->arr->direccion[i]);
    }
}