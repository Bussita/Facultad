/*
    La idea es almacenar los juegos de la persona quien primero lo ingrese en un tabla hash,
    si alguna otra persona ingresa el mismo numero de juego y coliciona entonces se marca con un 1 una matriz
    que llevara quien es amigo con quien (se dejara sin usar la fila y columna (0, 0) de la matriz).
    En caso que no haya colicion se agrega el dato (numero de juego) y tambien en la casilla se marca el 
    numero de persona (la persona a la cual le gusta ese juego y fue la primera en ingresarlo).

    Luego de ingresar todos los juegos de todas las personas queda una matriz con los pares de amigos, recorremos
    la matriz y los contamos.


    * Podria haber utilizado el array de personas y la matriz desde la posicion cero.
*/

#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct _Persona {
    int cantJuegos;
    int* juegos;
};

typedef struct _CasillaHash {
    void* dato;
    int persona;
    int eliminado;
} CasillaHash;

struct _TablaHash {
  CasillaHash *arr;
  unsigned nelems;
  unsigned size;
  FuncionCopiadora copy;
  FuncionComparadora comp;
  FuncionDestructora destroy;
  FuncionHash hash;
};

struct _Matriz {
    int** arr;
    int filas;
    int cols;
};

MatrizAux matriz_crear(int filas, int cols) {
    MatrizAux matriz = malloc(sizeof(struct _Matriz));

    matriz->arr = malloc(sizeof(int*) * filas);

    for (int i = 0; i < filas; i++) {
        matriz->arr[i] = calloc(cols, sizeof(int));
    }

    matriz->filas = filas;
    matriz->cols = cols;

    return matriz;
}

void matriz_destruir(MatrizAux matriz) {
    if (matriz == NULL) return;

    for (int i = 0; i < matriz->filas; i++) {
        free(matriz->arr[i]);
    }

    free(matriz->arr);
    free(matriz);
}

void matriz_escribir(MatrizAux matriz, int dato, int fila, int col) {
    // assert(fila < matriz->filas && col < matriz->cols && fila > 0 && col > 0);
    matriz->arr[fila][col] = dato;
}

int matriz_leer(MatrizAux matriz, int fila, int col) {
    // assert(fila < matriz->filas && col < matriz->cols && fila > 0 && col > 0);
    return matriz->arr[fila][col];
}

int matriz_contar_dato(MatrizAux matriz, int dato) {
    int aparicionesDato = 0;
    for (int i =0 ; i < matriz->filas; i++) {
        for (int j = 0; j < matriz->cols; j++) {
            if (matriz_leer(matriz, i, j) == dato) aparicionesDato++;
        }
    }

    return aparicionesDato;
}

void matriz_imprimir(MatrizAux matriz) {
    for (int i = 0; i < matriz->filas; i++) {
        for (int j = 0; j < matriz->cols; j++) {
            printf("%d | ", matriz_leer(matriz, i, j));
        }
        puts("");
    }
    puts("");
}

// ----------------------------------------------------------------
// ----------------------------------------------------------------

TablaHash tablahash_crear(unsigned int size, FuncionCopiadora copy, FuncionDestructora destroy ,FuncionComparadora comp, FuncionHash hash) {

  TablaHash tabla = malloc(sizeof(struct _TablaHash));
  assert(tabla != NULL);

  tabla->arr = malloc(sizeof(CasillaHash) * size);
  assert(tabla->arr != NULL);

  tabla->nelems = 0;
  tabla->size = size;

  tabla->copy = copy;
  tabla->comp = comp;
  tabla->destroy = destroy;
  tabla->hash = hash;

  for (unsigned int idx = 0; idx < size; ++idx) {
    tabla->arr[idx].dato = NULL;
    tabla->arr[idx].persona = 0;
    tabla->arr[idx].eliminado = 0;
  }

  return tabla;
}

unsigned int tablahash_nelems(TablaHash tabla) {
    if (tabla == NULL) return -1;

    return tabla->nelems;
}

unsigned int tablahash_size(TablaHash tabla) {
    if (tabla == NULL) return -1;

    return tabla->size;
}

void tablahash_destruir(TablaHash tabla) {
    if (tabla == NULL) return;

    for (unsigned int i =0; i < tabla->size; i++) {
        if (tabla->arr[i].dato != NULL) {
            tabla->destroy(tabla->arr[i].dato);
        }
    }

    free(tabla->arr);
    free(tabla);
}

static unsigned int rehash(TablaHash tabla, unsigned int idx) {
    return (idx + 1) % tabla->size;
}

static unsigned int tablahash_buscar_idx(TablaHash tabla, void* dato) {
    if (tabla == NULL || dato == NULL) return -1;

    // Calculamos la clave que deberia tener en la tabla hash
    unsigned int idx = tabla->hash(dato) % tabla->size;

    if (tabla->arr[idx].dato == NULL && tabla->arr[idx].eliminado == 0) return (unsigned int)-1;

    else if (tabla->arr[idx].dato != NULL && tabla->comp(tabla->arr[idx].dato, dato) == 0) return idx;

    else {

        unsigned int i = idx;
        int encontrado = -1;

        do {

            i = rehash(tabla, i);

            if (tabla->arr[i].dato != NULL) {
                encontrado = tabla->comp(tabla->arr[i].dato, dato);
            }

        } while (idx != i && encontrado != 0);
        
        return idx != i ? i : (unsigned int)-1;
    }

}

static void tablahash_redimencionar(TablaHash tabla, MatrizAux matriz) {
    if (tabla == NULL) return;

    CasillaHash* oldArr = tabla->arr;
    unsigned int oldSize = tabla->size;

    tabla->size = tabla->size * 2;
    tabla->arr = malloc(sizeof(CasillaHash) * tabla->size);
    tabla->nelems = 0;

    for (unsigned int i = 0; i < tabla->size; i++) {
        tabla->arr[i].dato = NULL;
        tabla->arr[i].eliminado = 0;
        tabla->arr[i].persona = 0;
    }

    for (unsigned int i = 0; i < oldSize; i++) {
        if (oldArr[i].dato != NULL) {
            tablahash_insertar(tabla, oldArr[i].dato, oldArr[i].persona, matriz);
            tabla->destroy(oldArr[i].dato);
        }
    }

    free(oldArr);
}

void tablahash_insertar(TablaHash tabla, void *dato, int persona, MatrizAux matriz) {
    if (tabla == NULL || dato == NULL) return;

    float factorCarga = (float)tabla->nelems / (float)tabla->size;

    if (factorCarga >= FACTOR_MAXIMO_CARGA) {
        tablahash_redimencionar(tabla, matriz);
    }

    // Calculemos la clave que deberia tener el dato dentro de la tabla
    unsigned int idx = tabla->hash(dato) % tabla->size;
    
    // Calculemos el idx que tiene el dato dentro de la tabla, en caso de no estar -1
    unsigned int idxIn = tablahash_buscar_idx(tabla, dato);

    if ((unsigned int)-1 != idxIn) {
        matriz_escribir(matriz, 1, tabla->arr[idxIn].persona, persona);

        return;
    }

    else {
        for (; tabla->arr[idx].dato != NULL; idx = rehash(tabla, idx));

        tabla->arr[idx].dato = tabla->copy(dato);
        tabla->arr[idx].persona = persona;
        tabla->arr[idx].eliminado = 0;

        tabla->nelems++;

        return;
    }
}

void tablahash_recorrer(TablaHash tabla, FuncionVisitante visit) {
    for (unsigned int i = 0; i < tabla->size; i++) {
        printf("IDX: %d - ", i);
        if (tabla->arr[i].dato != NULL) {
            visit(tabla->arr[i].dato);
        }
        puts("");
    }
    puts("");
}

// ----------------------------------------------------------------
// ----------------------------------------------------------------

static void* int_copiar(void* n) {
    int* newN = malloc(sizeof(int));

    *newN = *((int*)n);

    return (void*)newN;
}

static void int_destruir(void* n) {
    free((int*)n);
}

static int int_comparar(void* n1, void* n2) {
    return *((int*)n1) - *((int*)n2);
}

static unsigned int int_hash(void* n) {
    return ((*((int*)n) + 3) * 11);
}

int contar_amistades(Persona* personas, int cantPersonas) {
    MatrizAux matriz = matriz_crear(cantPersonas + 1, cantPersonas + 1);

    TablaHash tabla = tablahash_crear(cantPersonas, int_copiar, int_destruir, int_comparar, int_hash);

    int* dato = malloc(sizeof(int));

    for (int i = 1; i <= cantPersonas; i++) {
        for (int j = 0; j < personas[i].cantJuegos; j++) {
            *dato = (personas[i]).juegos[j];
            tablahash_insertar(tabla, dato, i, matriz);
        }
    }

    int paresAmigos = matriz_contar_dato(matriz, 1);

    free(dato);
    tablahash_destruir(tabla);
    matriz_destruir(matriz);

    return paresAmigos;
}

Persona* leer_datos(char* path, int* cantPersonas) {
    FILE* file = fopen(path, "r");

    fscanf(file, "%d", cantPersonas);

    // Consumo el \n
    char buffer[10];
    fgets(buffer, 10, file);

    Persona* personas = malloc(sizeof(Persona) * ((*cantPersonas) + 1));

    int cantJuegos;
    int juegoBuffer;

    for (int i = 1; i <= *cantPersonas; i++) {
        Persona persona;
        fscanf(file, "%d", &cantJuegos);
        persona.cantJuegos = cantJuegos;
        persona.juegos = malloc(sizeof(int) * cantJuegos);
        for (int j = 0; j < cantJuegos; j++) {
            fscanf(file, "%d", &juegoBuffer);
            persona.juegos[j] = juegoBuffer;
        }
        personas[i] = persona;
    }

    fclose(file);

    return personas;
}

void persona_destruir(Persona persona) {
    free(persona.juegos);
}

// Destruye personas desde la posicion 1 del array, quedo asi debido a que decidir no utilizar la casilla 0 del array
// de personas 
void personas_destruir(Persona* personas, int cantPersonas) {
    for (int i = 1; i <= cantPersonas; i++) {
        if (personas[i].juegos != NULL) {
            persona_destruir(personas[i]);
        }
    }

    free(personas);
}

void personas_imprimir(Persona* personas, int cant_personas) {
    for (int i = 1; i <= cant_personas; i++) {
        Persona persona = personas[i];
        printf("p%d - CantJuegos: %d - Juegos: ", i, persona.cantJuegos);
        for (int j = 0; j < persona.cantJuegos; j++) {
            printf("%d ", persona.juegos[j]);
        }
        puts("");
    }
}