#include <stdio.h>

// Declaramos la estructura punto
typedef struct {

    float x;
    float y;

} Punto;


Punto medio(Punto* p1, Punto* p2);


int main(){

    Punto p1,p2;

    p1.x = 1;
    p1.y = 1;

    p2.x = 5;
    p2.y = 5;

    Punto punto_medio = medio(&p1,&p2);

}


Punto medio(Punto* p1, Punto* p2){

    Punto punto_medio;

    punto_medio.x = (p1->x + p2->x) / 2;
    punto_medio.y = (p1->y + p2->y) / 2;

    return punto_medio;
}
