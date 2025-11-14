#ifndef __ARREGLO_ENTEROS_H__
#define __ARREGLO_ENTEROS_H__


typedef struct {

    int* direccion;
    int capacidad;
    
} ArregloEnteros;


ArregloEnteros* arreglo_enteros_crear(int capacidad);

void arreglo_enteros_destruir(ArregloEnteros* arreglo);

int arreglo_enteros_leer(ArregloEnteros* arreglo, int pos);

void arreglo_enteros_escribir(ArregloEnteros* arreglo, int pos, int dato);

int arreglo_enteros_capacidad(ArregloEnteros* arreglo);

void arreglo_enteros_imprimir(ArregloEnteros* arreglo);

void arreglo_enteros_ajustar(ArregloEnteros* arreglo, int capacidad);

void arreglo_enteros_insertar(ArregloEnteros* arreglo, int pos, int dato);

void arreglo_enteros_eliminar(ArregloEnteros* arreglo, int pos);



#endif