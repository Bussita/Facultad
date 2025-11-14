#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAM_MAZO 48
#define PALO 4
#define NUMERO 12

typedef struct {

    int palo; // Numeros de 1 a 4
    int numero; // Numeros de 1 a 12
    
} Carta;


typedef struct {

    Carta cartas[TAM_MAZO];

} Mazo;


void llenar(Mazo* mazo);

Carta azar(Mazo mazo);


int main(){


    Mazo mazo;

    llenar(&mazo);

    Carta cartaRandom = azar(mazo);

    printf("Carta elegida: (%d,%d)\n",cartaRandom.numero,cartaRandom.palo);

    return 0;
}


void llenar(Mazo* mazo){

    for (int palo = 1 ; palo <= PALO ; palo++){

        for(int numero = 1 ; numero <= NUMERO ; numero++){

            mazo->cartas[(palo - 1) * NUMERO + (numero - 1)].numero = numero;
            mazo->cartas[(palo - 1) * NUMERO + (numero - 1)].palo = palo;
            
        }
    }
}



Carta azar(Mazo mazo){
    
    srand(time(NULL));
    return mazo.cartas[rand() % TAM_MAZO];
}