#include <stdlib.h>
#include "functions.h"
#include <assert.h>
#include <stdio.h>

struct _SNodo{
    int value;
    int index;
    int cantMenores;
    struct _SNodo* next;
};
SList crear_secuencia_vacia(){return NULL;}

static SNodo* crear_nodo(int value, int index, int cantMenores, SNodo* next){
    SNodo* nuevoNodo = malloc(sizeof(nuevoNodo));
    nuevoNodo->value = value;
    nuevoNodo->index = index;
    nuevoNodo->cantMenores = 0;
    nuevoNodo->next = next;
    return nuevoNodo;
}
SList agregar_numero_a_secuencia(SList secuencia, int numero){
    if(secuencia == NULL){
        return crear_nodo(numero,0,0,NULL);
    }
    SNodo* nuevoNodo = crear_nodo(numero,secuencia->index+1, 0,secuencia);
    for(SNodo* temp = secuencia; temp!= NULL; temp=temp->next){
        if(nuevoNodo->value > temp->value) nuevoNodo->cantMenores++;
    }
    return nuevoNodo;
}

int* buscar_por_cantidadMenores(SList secuencia, int cantDeseada){
    int capacidadArray=100,capacidadActual = 0;
    int* elementos = malloc((sizeof(int) * capacidadArray));
    for(SNodo* temp = secuencia; temp!=NULL; temp=temp->next){
        if(temp->cantMenores == cantDeseada){
            if(capacidadActual == capacidadArray-1){
                capacidadArray*=2;
                elementos = realloc(elementos, capacidadArray);
            }
            elementos[capacidadActual] = temp->value;
        }
    }
    elementos = realloc(elementos, capacidadActual-1);
    return elementos;
}


SList secuencia_insertar_en_posicion(SList secuencia, int value, int pos){
    SNodo* nuevoNodo = crear_nodo(value, pos, 0, NULL), *temp = secuencia;
    if(secuencia!=NULL) assert(pos<=secuencia->index+1 && pos>=0);
    if(secuencia == NULL){
        assert(pos == 0);
        return nuevoNodo;
    }
    for(;temp->next!=NULL && temp->index < pos; temp=temp->next){
            if(value < temp->value) temp->cantMenores++;
            temp->index++;
    }
    if(value < temp->value) temp->cantMenores++;
    temp->index++;
    nuevoNodo->next = temp->next;
    temp->next = nuevoNodo;
    for(temp = nuevoNodo->next; temp!=NULL; temp=temp->next){
        if(temp->value < nuevoNodo->value) nuevoNodo->cantMenores++;
    }
    return nuevoNodo;
}
SList secuencia_eliminar_en_posicion(SList secuencia, int dato, int posicion){
    if(secuencia == NULL) return NULL;
    if(secuencia!=NULL) assert(posicion<=secuencia->index && posicion>=0);
    SNodo* temp = secuencia;
    for(;temp->index<posicion;temp=temp->next){
        temp->index--;
    }
    SNodo* nodeToDelete = temp;
    temp->next = nodeToDelete->next;
    for(temp = secuencia; temp!=NULL; temp=temp->next){
        if(temp->index > posicion && temp->value > nodeToDelete->value) temp->cantMenores--;
    }
    free(nodeToDelete);
    return secuencia;
}

void imprimir_secuencia(SList secuencia){
    for(;secuencia!=NULL;secuencia=secuencia->next) printf("Indice: %d Valor: %d CantMenores: %d\n",secuencia->index, secuencia->value, secuencia->cantMenores);
}
void swapearDato_swapearCantMenores(SNodo* p1, SNodo* p2){
    int aux = p1->cantMenores;
    p1->cantMenores = p2->cantMenores;
    p2->cantMenores = aux;
    int aux = p1->value;
    p1->value = p2->value;
    p2->value = aux;
}
SList ordernar_por_cantmenores(SList secuencia){
    if(secuencia == NULL) return secuencia;
    if(secuencia ->next == NULL) return secuencia;
    if(secuencia->cantMenores > secuencia->next->cantMenores){
        swapPointers(&secuencia, &secuencia->next);
        secuencia = ordernar_por_cantmenores(secuencia->next);
    }
    return secuencia;
}