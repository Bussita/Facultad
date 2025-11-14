#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

typedef struct _SNodo SNodo;
typedef SNodo* SList;

SList crear_secuencia_vacia();

SList agregar_numero_a_secuencia(SList secuencia, int);


void imprimir_secuencia(SList secuencia);

int* buscar_por_cantidadMenores(SList secuencia, int cantDeseada);

SList secuencia_insertar_en_posicion(SList secuencia, int value, int pos);
SList secuencia_eliminar_en_posicion(SList secuencia, int value, int pos);

SList ordernar_por_cantmenores(SList secuencia);
#endif