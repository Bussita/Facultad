#include <stdio.h>

void swap(int* x, int* y);


int main(){

    int x = 10;
    int y = 300;

    swap(x,y);

    return 0;

}

void swap(int* x ,int* y){

    int intercambio;

    intercambio = *x;
    *x = *y;
    *y = intercambio;

    return;
}

