#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef enum {

    BASTO,
    ESPADA,
    ORO,
    COPA

} Palo;



typedef struct Carta_{
    
    int x;
    Palo palo;

} Carta;

void crearMazo(Carta mazo[]){

    Palo palos[] = {BASTO, ESPADA, ORO, COPA};
    int contador=0;
    for(int i=0; i<12; i++){
        for(int j=0;j<4;j++){
            mazo[contador].x= i+1;
            mazo[contador].palo = palos[j];
            printf("Carta aniadida: %d de %d\n",mazo[contador].x,mazo[contador].palo);
            contador++;
        }
    }
}

Carta azar(Carta mazo[]){
    srand(time(NULL));
    int numeroAleatorio = rand() % 49;
    return mazo[numeroAleatorio];
}
int main(){
    Carta mazo[48], cartaAleatoria;

    crearMazo(mazo);
    cartaAleatoria = azar(mazo);
    printf("La carta aleatoria generada fue el %d de %d", cartaAleatoria.x, cartaAleatoria.palo);
    return 0;
}


