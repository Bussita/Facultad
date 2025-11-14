#include <stdio.h>
#include <stdlib.h>
#include "arreglo_enteros.h"

#define min(x,y) (x < y) ? x : y 




ArregloEnteros* arreglo_enteros_crear(int capacidad) {

    ArregloEnteros* nuevo_arreglo = malloc(sizeof(ArregloEnteros));

    nuevo_arreglo->direccion = calloc(sizeof(int), capacidad);

    nuevo_arreglo->capacidad = capacidad;

    return nuevo_arreglo;

}



void arreglo_enteros_destruir(ArregloEnteros* arreglo) {

    free(arreglo->direccion);
    free(arreglo);
}



// En esta funcion asumimos que el arreglo de enteros tiene al menos un elemento
int arreglo_enteros_leer(ArregloEnteros* arreglo, int pos) {

    // Si la posicion que queres leer excede a la capacidad, leemos el ultimo
    if (pos >= arreglo->capacidad)
        return arreglo->direccion[arreglo->capacidad - 1];

    // Si la posicion que queres leer es menor a 0, leemos el primero
    if (pos < 0)
        return arreglo->direccion[0]; 

    // En caso contrario, leemos el entero de la posicion deseada
    return arreglo->direccion[pos];
}



void arreglo_enteros_escribir(ArregloEnteros* arreglo, int pos, int dato) {

    // Si el arreglo no tiene elementos, no modificamos nada
    if (arreglo->capacidad == 0)
        return;

    // Si la posicion que queres modificar excede a la capacidad, escribimos el ultimo
    if (pos >= arreglo->capacidad) {
        arreglo->direccion[arreglo->capacidad - 1] = dato;
        return;
    }

    // Si la posicion que queres modificar es menor a 0, escribimos el primero
    if (pos < 0) {
        arreglo->direccion[0] = dato;
        return;
    }

    // Si la posicion es correcta, escribimos en dicha posicion
    arreglo->direccion[pos] = dato;
}



int arreglo_enteros_capacidad(ArregloEnteros* arreglo) {

    return arreglo->capacidad;
}



void arreglo_enteros_imprimir(ArregloEnteros* arreglo) {

     for (int i = 0 ; i < arreglo->capacidad ; i++) 
          printf("%d\n", arreglo->direccion[i]);
     
     return;
}



void arreglo_enteros_ajustar(ArregloEnteros* arreglo, int capacidad) {

    // Si la capacidad es negativa, no hacemos nada
    if (capacidad < 0)
        return;

    // Si la nueva capacidad es 0
    if (capacidad == 0) {
        free(arreglo->direccion);

        arreglo->direccion = NULL;
        arreglo->capacidad = 0;

        return;
    }

    // Si la nueva capacidad es positiva
    int* nueva_direccion = malloc(sizeof(int) * capacidad);

    // Vemos hasta donde debemos leer los elementos
    int limite = min(capacidad,arreglo->capacidad);

    for (int i = 0 ; i < limite ; i++)
        nueva_direccion[i] = arreglo->direccion[i];

    free(arreglo->direccion);

    arreglo->direccion = nueva_direccion;
    arreglo->capacidad = capacidad;
}



void arreglo_enteros_insertar(ArregloEnteros* arreglo, int pos, int dato) {

    int* nueva_direccion = malloc(sizeof(int) * (arreglo->capacidad + 1));

    // Si la posicion en donde queres agregar excede o iguala la capacidad, se agrega a lo ultimo
    if (pos >= arreglo->capacidad) {

        for (int i = 0 ; i < arreglo->capacidad ; i++)
            nueva_direccion[i] = arreglo->direccion[i];

        nueva_direccion[arreglo->capacidad] = dato;

        free(arreglo->direccion);

        arreglo->direccion = nueva_direccion;
        arreglo->capacidad += 1;

        return;
    }

    // Si la posicion en donde queres agregar es menor a 0, se agrega al principio
     if (pos < 0) {

          for (int i = 1 ; i <= arreglo->capacidad ; i++)
               nueva_direccion[i] = arreglo->direccion[i - 1];

          nueva_direccion[0] = dato;

          free(arreglo->direccion);

          arreglo->direccion = nueva_direccion;
          arreglo->capacidad += 1;
        
          return;
     }

    // En caso que sea correcta la posicion, 
    for (int i = 0 ; i < arreglo->capacidad ; i++) {

          if (i < pos)
               nueva_direccion[i] = arreglo->direccion[i];

          else
               nueva_direccion[i + 1] = arreglo->direccion[i];

    }

    // Ingresamos el dato en la posicion deseada
    nueva_direccion[pos] = dato;

     free(arreglo->direccion);

     arreglo->direccion = nueva_direccion;
     arreglo->capacidad += 1;

}


void arreglo_enteros_eliminar(ArregloEnteros* arreglo, int pos) {

    // Si la posicion es incorrecta, no eliminamos ningun elemento
    if (pos < 0 || pos >= arreglo->capacidad)
        return;

    // Si solo existe un elemento, nos queda un arreglo vacio
    if (arreglo->capacidad == 1) {

        free(arreglo->direccion);

        arreglo->direccion = NULL;
        arreglo->capacidad = 0;

        return;
    }

    // Si la posicion es correcta, realizamos los corrimientos necesarios
    int* buffer = malloc(sizeof(int) * (arreglo->capacidad - 1));

    for (int i = 0 ; i < arreglo->capacidad - 1 ; i++) {

        // Si es menor, mantenemos los elementos
        if (i < pos)
            buffer[i] = arreglo->direccion[i];
        
        // Si nos pasamos, corremos los elementos
        else
            buffer[i] = arreglo->direccion[i + 1];
    }

    free(arreglo->direccion);

    arreglo->direccion = buffer;
    arreglo->capacidad -= 1;

    return;
}