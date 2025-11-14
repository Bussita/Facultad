#include <stdio.h>

void set_int(int *valor);

int main(){

    int valor1 = 3;
    int valor2 = 0;

    set_int(&valor1);
    set_int(&valor2);

    return 0;
}

void set_int(int *valor){

    if (*valor) // Si es distinto de 0
        *valor = 1;
    else
        *valor = 0;
}