#include <stdio.h>

void set_first(int *array);

int main(){

  int arreglo[10];
  set_first(arreglo);

  return 0;
}


void set_first(int *array){

  array[0] = 0;
  printf("El valor del primer elemento es: %d\n",array);

}