#include <stdio.h>
#include <stdlib.h>

int fibonacciR(int number){
    if(number == 0) return 0;
    if(number == 1) return 1;
    return fibonacciR(number - 1) + fibonacciR(number - 2);
}

long fibonacciIterativo(int number){
    long serie[200];
    serie[0] = 0;
    serie[1] = 1;
    for(int i=2; i<number; i++){
        serie[i] = serie[i-1] + serie[i-2];
    }
    long resultado = serie[number-1] + serie[number-2];
    return resultado;
}

int expo(int b,unsigned int n){
    if(n==1){
        return b;
    }else{
        return b*expo(b, n-1);
    }
}

int maximo(int* array, unsigned int longitud){
    int indice=0, max=array[0];
    for(int i = 1; i<longitud; i++){
        if(array[i] > max){
            max = array[i];
            indice = i;
        }
    }
    return indice;
}

int main(){
    char a = 0;
    printf("el caracter es %c\n",a);
    return 0;

}

