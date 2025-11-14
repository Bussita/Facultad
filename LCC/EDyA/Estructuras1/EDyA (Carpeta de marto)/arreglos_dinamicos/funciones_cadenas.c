#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "arreglo_enteros.h"

// Definimos macro para calcular minimo entre dos numeros
#define min(x,y) x<y ? x : y 

int string_len(char* str);

void string_reverse(char* str);

int string_concat(char* str1, char* str2, int max);

int string_compare(char* str1, char* str2);

int string_subcadena(char* str1, char* str2);

void string_unir(char* arreglo_strings[], int n, char* sep, char* res);


int main() {


    //char* arreglo_string[] = {"Hello World!","Viva Argentina","Viva Messi!"};

    //char separador[] = " and ";

    //char* resultado = malloc(sizeof(char) * 1000);

    //string_unir(arreglo_string, 3, separador, resultado);

    //printf("%s\n",resultado);

    //free(resultado);

    char str1[] = "batatas";
    char str2[] = "atas";

    printf("Longitud de str1: %d\n", string_len(str1));

    printf("%d\n",string_subcadena(str1,str2));

    return 0;
}


int string_len(char* str) {

    char* final;

    for (final = str ; *final != '\0' ; final++);

    return final - str;
}


void string_reverse(char* str) {

    int longitud = string_len(str);

    int medio = longitud / 2;

    char buffer;

    for (int i = 0 ; i < medio ; i++) {

        buffer = str[i];
        str[i] = str[longitud - i - 1];
        str[longitud - i - 1] = buffer;
    }
}


int string_concat(char* str1, char* str2, int max) {

    int largo_str1 = string_len(str1);

    int largo_str2 = string_len(str2);

    int maximo_copiado = min(max,largo_str2);

    for (int i = 0 ; i < maximo_copiado ; i++)

        str1[largo_str1 + i] = str2[i];

    str1[largo_str1 + maximo_copiado] = '\0';

    return maximo_copiado;

}


int string_compare(char* str1, char* str2) {

    int limite_comparacion = min(string_len(str1), string_len(str2));

    int resultado = 0;

    int i = 0;

    // Podria mejorar la condicion haciendo que no lleguen al terminador en 
    // lugar de llegar al limite de comparacion.
    while (i <= limite_comparacion && resultado == 0) {

        if (str1[i] > str2[i])
            resultado = 1;
        
        if (str1[i] < str2[i])
            resultado = -1;

        i++;
    }

    return resultado;
}


// PREGUNTAR RESOLUCION Y VER ALGORITMO KNUTH - MORRIS - PRATT
int string_subcadena(char* str1, char* str2) {

    int indice1 = 0, indice2 = 0;

    int largo_str1 = string_len(str1);

    int inicio, indice_ocurrencia = -1; 

    while (indice_ocurrencia == -1 && indice1 < largo_str1) {

        // Si no coinciden, directamente incrementamos
        if (str1[indice1] != str2[indice2]) 
            indice1++;
        
        else {

            inicio = indice1;

            while (str1[indice1] != '\0' && str2[indice2] != '\0' && str1[indice1] == str2[indice2]) {
                indice1++;
                indice2++;
            }

            // Si llegamos al final de la segunda palabra, encontramos la subcadena
            if (str2[indice2] == '\0')
                indice_ocurrencia = inicio; 


            // Si llegamos al final de la primer palabra, forzamos la terminacion
            if (str1[indice1] == '\0')
                indice1 = largo_str1;

            // Si no coinciden, empezamos a buscar desde el siguiente
            if (str1[indice1] != str2[indice2]) {
                indice1 = inicio + 1;
                indice2 = 0;
            }
        }
    }

    return indice_ocurrencia;
}



void string_unir(char* arreglo_strings[], int n, char* sep, char* res) {

    int longitud_res;

    int longitud_total = 0;

    int longitud_sep = string_len(sep);

    // Recorremos todos los strings del arreglo
    for (int i = 0 ; i < n ; i++){

        longitud_res = string_len(arreglo_strings[i]);

        // Recorremos todas las letras del string
        for (int w = 0 ; w < longitud_res ; w++)

            res[longitud_total + w] = arreglo_strings[i][w];

        longitud_total += longitud_res;

        // Si no nos encontramos en la ultima palabra
        if (i != n - 1) {

            // Recorremos todas las letras del separador
            for (int s = 0 ; s < longitud_sep ; s++)

                res[longitud_total + s] = sep[s];
            
            longitud_total += longitud_sep;
            }
        }
        
    return;
}


