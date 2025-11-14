#include <stdlib.h>
#include "tablahashDA.h"
#include <assert.h>
#include <stdio.h>
#define MAX_CARGA 0.3

typedef struct{
    void* data;
    int DATOELIMINADO;
} CasillaHash;

struct _TablaHash{
    CasillaHash* elementos;
    float factorDeCarga;
    unsigned int numElems;
    unsigned int capacidad;
    FuncionComparadora cmp;
    FuncionCopiadora copy;
    FuncionDestructora dest;
    FuncionHash hash;
};

TablaHash tablahash_crear(unsigned int capacidad, FuncionCopiadora copy, FuncionComparadora cmp, FuncionDestructora destr, FuncionHash hash){
    TablaHash tabla = malloc(sizeof(struct _TablaHash));
    assert(tabla!=NULL);
    tabla->elementos = malloc(sizeof(CasillaHash)*capacidad);
    assert(tabla->elementos!=NULL);
    tabla->numElems = 0;
    tabla->capacidad = capacidad;
    tabla->factorDeCarga = 0;
    tabla->cmp = cmp;
    tabla->copy = copy;
    tabla->dest = destr;
    tabla->hash = hash;
    for(unsigned int idx = 0; idx<tabla->capacidad; idx++){
        tabla->elementos[idx].data = NULL;
        tabla->elementos[idx].DATOELIMINADO = 0;
    }
    return tabla;
}

unsigned int tablahash_capacidad(TablaHash tabla){return tabla->capacidad;}

unsigned int tablahash_numeroDeElementos(TablaHash tabla){return tabla->numElems;}

float tablahash_factorDeCarga(TablaHash tabla){return ((float)tabla->numElems/(float)tabla->capacidad);}

void tablahash_destruir(TablaHash tabla){
    for(unsigned int idx = 0; idx < tabla->capacidad; idx++){
        if(tabla->elementos[idx].data!=NULL){
            tabla->dest(tabla->elementos[idx].data);
        }
    }
    free(tabla->elementos);
    free(tabla);
}

void tablahash_insertar(TablaHash tabla, void* dato){
    if(tabla->factorDeCarga >= MAX_CARGA){
        tablahash_redimensionar(tabla);
    }
    // indice a insertar el elemento segun h(X)
    unsigned int idx = tabla->hash(dato) % tabla->capacidad;
    
    unsigned int newIdx = idx;
    int bandera = 1;
    do{
        if(tabla->elementos[newIdx].data==NULL){
            tabla->elementos[newIdx].data = tabla->copy(dato);
            bandera = 0;
        }else if(tabla->cmp(tabla->elementos[newIdx].data,dato)==0){
            tabla->dest(tabla->elementos[newIdx].data);
            tabla->elementos[newIdx].data = tabla->copy(dato);
            bandera = 0;
        }
        newIdx = (newIdx + 1) % tabla->capacidad;
    }while(bandera);
    tabla->numElems++;
    tabla->factorDeCarga = tablahash_factorDeCarga(tabla);
    return;
}

void* tablahash_buscar(TablaHash tabla, void* dato){
    unsigned int idx = tabla->hash(dato) % tabla->capacidad;
    if(tabla->elementos[idx].DATOELIMINADO==0 && tabla->cmp(tabla->elementos[idx].data, dato)==0){
        return tabla->elementos[idx].data;
    }
    unsigned int noSeEncontro = 0, bandera = 1;
    unsigned int newIdx = (idx+1) % tabla->capacidad;
    while(bandera){
        if(tabla->elementos[newIdx].DATOELIMINADO == 0){
        if(tabla->elementos[newIdx].data!=NULL && tabla->cmp(tabla->elementos[newIdx].data,dato)==0){
            break;
        }
        newIdx = (newIdx + 1) % tabla->capacidad;
        if(newIdx == idx){
            noSeEncontro = 1;
            break;
        }
        }else{
            newIdx = (newIdx + 1) % tabla->capacidad;
            continue;
        }
    }
    if(noSeEncontro == 1){ return NULL;}
    return tabla->elementos[newIdx].data;
}

void tablahash_redimensionar(TablaHash tabla){
    tabla->capacidad = tabla->capacidad * 2;
    tabla->factorDeCarga = tablahash_factorDeCarga(tabla);
    CasillaHash* nuevoArreglo = malloc(sizeof(CasillaHash) * tabla->capacidad);
    for(unsigned int idx = 0; idx < tabla->capacidad / 2; idx++){
        if(tabla->elementos[idx].DATOELIMINADO!=1 && tabla->elementos[idx].data!=NULL){
        unsigned newIdx = tabla->hash(tabla->elementos[idx].data) % tabla->capacidad;
        nuevoArreglo[newIdx].data = tabla->copy(tabla->elementos[idx].data);
        nuevoArreglo[newIdx].DATOELIMINADO = 0;
        }
    }
    free(tabla->elementos);
    tabla->elementos = nuevoArreglo;
}

void tablahash_eliminar(TablaHash tabla, void* dato){
    unsigned int idx = tabla->hash(dato) % tabla->capacidad;
    if(tabla->elementos[idx].DATOELIMINADO == 0 && tabla->cmp(tabla->elementos[idx].data,dato)==0){
        tabla->elementos[idx].DATOELIMINADO =1;
        return;
    }
    unsigned int newIdx = (idx + 1) % tabla->capacidad;
    while(newIdx!=idx){
        if(tabla->elementos[newIdx].DATOELIMINADO == 0 && tabla->cmp(tabla->elementos[newIdx].data,dato)==0){
            tabla->elementos[newIdx].DATOELIMINADO = 1;
            newIdx = idx;
        }else{
            newIdx = (newIdx + 1) % tabla->capacidad;
        }
    }
}