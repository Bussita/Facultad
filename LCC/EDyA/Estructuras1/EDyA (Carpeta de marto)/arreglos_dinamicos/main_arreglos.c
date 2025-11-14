#include "arreglo_enteros.h"
#include <stdio.h>
#include <stdlib.h>


int main(void) {

    ArregloEnteros* nuevo_arreglo = arreglo_enteros_crear(5); // Creamos el nuevo arreglo

     //arreglo_enteros_imprimir(nuevo_arreglo); //Porque me da error, si ya inicialize al puntero

     // Escribimos el arreglo
     for (int i = 0 ; i < arreglo_enteros_capacidad(nuevo_arreglo) ; i++)
          arreglo_enteros_escribir(nuevo_arreglo, i, 2*i);

     // Imprimimos todo el arreglo
     arreglo_enteros_imprimir(nuevo_arreglo);

     // Vemos de leer todo el arreglo
     for (int i = -1 ; i <= arreglo_enteros_capacidad(nuevo_arreglo) ; i++)
         printf("%d\n",arreglo_enteros_leer(nuevo_arreglo, i));


     // Ajustamos arreglo (funciona bien)
     arreglo_enteros_ajustar(nuevo_arreglo,10);
     for (int i = 4 ; i < arreglo_enteros_capacidad(nuevo_arreglo) ; i++)
          arreglo_enteros_escribir(nuevo_arreglo, i, 2*i);

     arreglo_enteros_imprimir(nuevo_arreglo);

     arreglo_enteros_ajustar(nuevo_arreglo,5);


     // Insertamos en arreglo (funciona bien)
     arreglo_enteros_insertar(nuevo_arreglo, -10, 35);
     arreglo_enteros_insertar(nuevo_arreglo, 100, 35);
     arreglo_enteros_insertar(nuevo_arreglo, 2 , 100);

     arreglo_enteros_imprimir(nuevo_arreglo);


     // Eliminamos de arreglo (funciona bien)
     arreglo_enteros_eliminar(nuevo_arreglo,7);
     arreglo_enteros_eliminar(nuevo_arreglo,2);
     arreglo_enteros_eliminar(nuevo_arreglo,0);


     arreglo_enteros_imprimir(nuevo_arreglo);

     arreglo_enteros_destruir(nuevo_arreglo);

    return 0;
}
