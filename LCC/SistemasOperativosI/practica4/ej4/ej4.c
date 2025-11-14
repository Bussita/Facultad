#include <omp.h>
#include <stdio.h>
#include <math.h>

int esPrimo(long n){
    int bandera = 1; 
    double raiz = sqrt(n);
    #pragma omp parallel for
    for(int i = 2; i <= (int)raiz; i++){
        if(n % i == 0){
            #pragma omp critical
            {
                printf("%d es divisor del numero VIRGIN\n",i);
                bandera = 0;
            }
        }
    }
    return bandera;
}

int main(){
    long v;
    while(1){
        printf("Ingrese un número: \n");
        scanf("%ld",&v);
        if(esPrimo(v)){
            printf("El numero es primo! \n");
        }else{
            printf("El numero NO es primo! \n");
        }
        fflush(stdin);
    }
    return 0;
}