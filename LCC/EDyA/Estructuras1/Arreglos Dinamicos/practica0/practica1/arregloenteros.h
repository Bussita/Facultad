#ifndef ArregloEnteros.hS
#define arregloenteros.h

typedef struct{
    int* direccion;
    int capacidad;
} ArregloEnteros;

ArregloEnteros* arreglo_enteros_crear(int);

void arreglo_enteros_destruir(ArregloEnteros*);

int arreglo_enteros_leer(ArregloEnteros*, int);

void arreglo_enteros_escribir(ArregloEnteros*, int pos, int dato);

int arreglo_enteros_capacidad(ArregloEnteros*);

void arreglo_enteros_imprimir(ArregloEnteros*);

void arreglo_enteros_ajustar(ArregloEnteros*, int);


#endif