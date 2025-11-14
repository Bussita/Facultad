#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int main(int argc, char* argv[]) {
    char* ruta_archivo = argv[1];
    int cant_personas;

    Persona* personas = leer_datos(ruta_archivo, &cant_personas);

    printf("cantPersonas: %d", cant_personas);
    puts("");

    personas_imprimir(personas, cant_personas);

    int resultado = contar_amistades(personas ,cant_personas);
    printf("Hay %d amistades en la carrera !\n", resultado);

    personas_destruir(personas, cant_personas);

    return 0;
}
