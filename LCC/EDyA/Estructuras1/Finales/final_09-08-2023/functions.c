#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include <assert.h>
/* La idea es hacer una matriz de adyacencia y funciones que agreguen las dichas etiquetas a la matriz.
    Las matrices de adyacencia tienen la particularidad de ser cuadradas, por lo que lo representaremos de dicha manera.
    Si en una entrada Aij no hay etiqueta, pondremos un 0, si hay una 'a' un 1, si hay una 'b' un 2 y finalmente si estan ambas etiquetas
    pondremos un 3*/

typedef struct Casilla{
    int a;
    int b;
}Casilla;
struct _MatrizAux{
    Casilla** arr;
    int dimension;
};

struct _Matriz{
    MatrizAux matriz;
    int* nodosAceptacion;
};

MatrizAux matriz_crear(int n){
    MatrizAux nuevaMatriz = malloc(sizeof(struct _MatrizAux));
    nuevaMatriz->arr = malloc(sizeof(int*)*n);
    for(int i = 0; i<n; i++){
        nuevaMatriz->arr[i] = calloc(n,sizeof(int));
    }
    nuevaMatriz->dimension = n;
    return nuevaMatriz;
}
void imprimir_entero(void* entero){
    printf("%d",*(int*)entero);
}

int matriz_leer(MatrizAux matriz, int i, int j){
    return matriz->arr[i][j];
}

void matriz_imprimir(MatrizAux matriz){
    for(int i = 0; i<matriz->dimension; i++){
        for(int j = 0; j<matriz->dimension; j++){
            printf("%d ",matriz->arr[i][j]);
        }
        puts("");
    }
    puts("");
}

void matriz_destruir(MatrizAux matriz, FuncionDestructora destroy){
    for(int i=0; i<matriz->dimension;i++){
        destroy(matriz->arr[i]);
    }
    destroy(matriz->arr);
    free(matriz);
}


Matriz leer_archivo(char* archivo){
    FILE* file = fopen(archivo,"r");
    int dimension;
    fscanf(file, "%d", &dimension);
    MatrizAux matriz = matriz_crear(dimension);
    char buffer[20];
    int j=0
    for(int i = 0; i<dimension; dimension++){
        fscanf(file,"%s",buffer);
        for(int indice=0; buffer[indice]!='\0'; i++){
            if(buffer[indice]=='a'){
                if(buffer[indice+1]==';'){
                    matriz->arr[i][j] = 1;
                }else{
                    matriz->arr[i][j] = 3;
                }
            }
            if(buffer[indice]=='b'){
                if(buffer[indice+1]==';'){
                    matriz->arr[i][j] = 2;
                }else{
                    matriz->arr[i][j] = 3;
                }
            }
        }
    }
}

Matriz agregar_transicion(Matriz adyacencia)