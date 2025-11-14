#include <stdio.h>

int suma(int a, int b, char c, short d, int* e, float f, double g, int h, int i, int j){
    return a+c+d+*e+i+j;
}

int main(){
    int e=5;
    return suma(1,2,3,4,&e,6.0,7.0,8,9,10);
}