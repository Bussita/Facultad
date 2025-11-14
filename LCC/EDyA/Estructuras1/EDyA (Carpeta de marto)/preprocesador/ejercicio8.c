#include <stdio.h>

#define SUMARRAY(array, size) ({int suma = 0 ; for (int i = 0 ; i < size ; suma += array[i++]) ; suma;})


int main() {

  int array[] = {1,2,3,4,5,6};

  printf("%d\n",SUMARRAY(array,6));

  return 0;
}