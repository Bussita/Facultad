#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    SList secuencia = crear_secuencia_vacia();
    secuencia = secuencia_insertar_en_posicion(secuencia,12,0);
    secuencia = secuencia_insertar_en_posicion(secuencia,30,1);
    secuencia = secuencia_insertar_en_posicion(secuencia,1,2);
    secuencia = secuencia_insertar_en_posicion(secuencia,2,3);

    printf("Secuencia\n");
    imprimir_secuencia(secuencia);

    secuencia = secuencia_insertar_en_posicion(secuencia, 4,0);
    secuencia = secuencia_insertar_en_posicion(secuencia, 10,3);
    secuencia = secuencia_insertar_en_posicion(secuencia, 20,4);
    secuencia = secuencia_insertar_en_posicion(secuencia, 100,0);
    printf("Secuencia nueva\n");
    imprimir_secuencia(secuencia);
    return 0;
}