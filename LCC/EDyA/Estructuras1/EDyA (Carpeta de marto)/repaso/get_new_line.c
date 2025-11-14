#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX_BUFFER 10
#define STR(s) STR2(s)
#define STR2(s) #s


char* get_new_line(void);

int main(){

    char* cadena1 = get_new_line();

    printf("Primera cadena: %s\n",cadena1);

    free(cadena1);


    char* cadena2 = get_new_line();

    printf("Segunda cadena: %s\n",cadena2);

    free(cadena2);

    return 0;
}



char* get_new_line(){

    char buffer[MAX_BUFFER + 1];
    char* new_line = NULL;
    char* buscador;

    size_t largoTotal = 0, largoActual = 0;

    int continuar = 1;

    while (continuar) {
        
        // scanf("%"STR(MAX_BUFFER)"[^\n]",buffer); Preguntar porque no funciona
        
        fflush(stdin);

        // fgets(buffer, MAX_BUFFER + 1, stdin);

        buscador = strchr(buffer,'\n');

        if (buscador != NULL) {

            *buscador = '\0';
            continuar = 0;

        }

        largoActual = strlen(buffer);

        new_line = realloc(new_line, sizeof(char) * (largoTotal + largoActual + 1));

        strcpy(new_line + largoTotal, buffer);

        largoTotal += largoActual;

    }

    return new_line;

}
