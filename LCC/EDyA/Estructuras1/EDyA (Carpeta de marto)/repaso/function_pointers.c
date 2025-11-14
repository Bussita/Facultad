#include <stdio.h>

int apply(int (*function)(int), int value);

void apply_in(int (*function)(int), int* value);

void recorre(void (*visitorFunc)(int), int* array, int value);

int sucesor(int n);

void imprimir(int n);

int main(){

    int valor = 4;
    int largo = 5;
    int array[] = {1,2,3,4,5};

    // Funcion (a)
    apply(&sucesor,valor);

    // Funcion (b)
    apply_in(&sucesor,&valor);

    // Funcion (c)
    recorre(&imprimir,array,largo);


    return 0;
}

int sucesor(int n){
    return n + 1;
}


void imprimir(int n){
    printf("%d \n",n);
}



int apply(int (*function)(int), int value){

    return function(value);

}


void apply_in(int (*function)(int), int* value){

    int pointer_value = *value;

    *value = function(pointer_value);

}


void recorre(void (*visitorFunc)(int), int* array, int length){

    for (int i = 0 ; i < length ; i++)
        visitorFunc(array[i]);

}