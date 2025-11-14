#include <stdio.h>
#include <stdlib.h>
#include "ordenamiento.h"

long binsearchR(long arr[], long low,long high, long value){
    if(low>high) return -1;
    long m = (low + high)/2;
    if(arr[m]==value) return m;
    if(arr[m]>value) return binsearchR(arr,low,m-1,value);
    return binsearchR(arr,m+1,high,value);
}

long binsearch(long arr[], long len, long value){
    long max = len - 1, min = 0;
    while(min<=max){
        long medio = min + (max - min)/2;
        if(arr[medio] == value){
            return medio;
        }else if(arr[medio] > value){
            max = medio-1;
        }else{
            min = medio+1;
        }
    }
    return -1;
}

void insertionSort(int array[], int largo){
    int i = 1;
    while(i < largo){
        int j = i-1;
        int mayores = array[i];
        while(j>=0 && array[j] > mayores){
            if(array[j] > array[j+1]){
                array[j+1] = array[j];
            }
        j--;
     }
    array[j+1] = mayores;
    i++;
    }
}

static int* mezclar(int* B1, int largo1, int* B2, int largo2){
    int* arregloOrdenado = malloc(sizeof(int)*(largo1+largo2));
    int i=0, j=0, k=0;
    while(i<largo1 && j<largo2){
        if(B1[i]<= B2[j]){
            arregloOrdenado[k]=B1[i];
            k++;
            i++;
        }else{
            arregloOrdenado[k]=B2[j];
            k++;
            j++;
        }
    }
    while(i < largo1){
        arregloOrdenado[k] = B1[i];
        k++;
        i++;
    }
    while(j < largo2){
        arregloOrdenado[k] = B2[j];
        k++;
        j++;
    }
    return arregloOrdenado;
}

int* mergeSort(int* arr, int largo){
    if(largo < 2){
        int* copia = malloc(sizeof(int) * largo);
        if(largo == 1) copia[0] = arr[0];
        return copia;
    }else{
        int m = largo/2;
        int* primerMitad = malloc(sizeof(int)*(m));
        for(int i=0; i<m; i++) primerMitad[i] = arr[i];
        int* segundaMitad = malloc(sizeof(int)*(largo-m));
        for(int i=m; i<largo; i++) segundaMitad[i-m] = arr[i];
        int* B1 = mergeSort(primerMitad,m);
        int* B2 = mergeSort(segundaMitad,largo-m);
        int* arregloOrdenado = mezclar(B1,m,B2,largo-m);
        free(primerMitad);
        free(segundaMitad);
        free(B1);
        free(B2);
        return arregloOrdenado;
    }
}
static void swapInt(int* x, int* y){
    int aux = *x;
    *x = *y;
    *y = aux;
}

int particionLomuto(int* arr,int n, int pivot){
    int j = -1;
    for(int i=0;i<n;i++){
        if(arr[i] <= pivot){
            j++;
            swapInt(&arr[i],&arr[j]);
        } 
    }
    return j;
}

void quickSort(int* arr, int n){
    if(n < 2) return;
    int pivote = arr[0];
    int nizq = 1 + particionLomuto(&arr[1], n-1, pivote);
    swapInt(&arr[0],&arr[nizq]);
    quickSort(arr,nizq);
    quickSort(&arr[nizq+1], n-nizq-1);
}

