#include <stdio.h>
#include <stdlib.h>

// Complejidad logaritmica: O(n) = n
int encontrar_pico(int A[], int N){

  if (N == 1)
    return 0;
  
  int indice = -1;  

  for (int i = 0 ; i < N && indice == -1 ; i++) {

    // Si nos encontramos en extremo izquierdo
    if (i == 0 && A[i] >= A[i + 1])
      indice = 0;

    // Si nos encontramos en extremo derecho
    if (i == N - 1 && A[i] >= A[i - 1])
      indice = N - 1;

    // Si nos encontramos en el medio
    if ((i > 0 && i < N - 1) && (A[i] >= A[i - 1] && A[i] >= A[i + 1]))
      indice = i;

  }

  return indice;
}



// Complejidad logaritmica: O(n) = log(n)
int find_peak(int a[], int n) {

  // Set the first limits
  int bot = 0;
  int top = n - 1;

  int middle;

  int index = -1; // We considered that it doesnt exist a peak 

  while (bot <= top && index == -1) {

    // We calculate the middle
    middle = (top + bot) / 2;

    // If we are in the left corner
    if (middle == 0 && a[0] >= a[1])
      index = 0;

    // If we are in the right  corner
    else if (middle == n - 1 && a[n - 1] >= a[n - 2])
      index = n - 1;

    // If we are in the center
    else if (a[middle] >= a[middle - 1] && a[middle] >= a[middle + 1])
      index = middle;

    // If we do not find a peak, we change the limits 
    else {
        
        // Increase the bot
        if ((a[middle - 1] - a[middle]) <= (a[middle + 1] - a[middle])) 
          bot = middle + 1;

        // Reduce the top
        else
          top = middle - 1;
    }
  }

  return index;
}

int main(void) {

  int array1[] = {1,2,3,4,5,6,7};
  int array2[] = {6,5,4,3,2,1};
  int array3[] = {1,2,3,4,3,2,1};
  int array4[] = {1,15,3,4,8};
  int array5[] = {1,2,3,4,5,4,3};
  int array6[] = {8,4,3,15,1};
  int array7[] = {1,2,2,2};
  
  int extra_large = 1000000000;
  int* a = malloc(sizeof(int) * extra_large);

  // We fill the entire array (REAL: 3,153 ; USER: 1,927)
  for (int i = 0 ; i < extra_large ; i++)
    a[i] = i;


  // Try with big arrays
  printf("encontrar_pico: %d\n",encontrar_pico(a,extra_large));
  printf("find_peak: %d\n",find_peak(a,extra_large));

  // Try with small arrays
  // printf("encontrar_pico: %d\nfind_peak: %d\n\n",encontrar_pico(array1,7),find_peak(array1,7));
  // printf("encontrar_pico: %d\nfind_peak: %d\n\n",encontrar_pico(array2,6),find_peak(array2,6));
  // printf("encontrar_pico: %d\nfind_peak: %d\n\n",encontrar_pico(array3,7),find_peak(array3,7));
  // printf("encontrar_pico: %d\nfind_peak: %d\n\n",encontrar_pico(array4,5),find_peak(array4,5));
  // printf("encontrar_pico: %d\nfind_peak: %d\n\n",encontrar_pico(array5,7),find_peak(array5,7));
  // printf("encontrar_pico: %d\nfind_peak: %d\n\n",encontrar_pico(array6,5),find_peak(array6,5));
  // printf("encontrar_pico: %d\nfind_peak: %d\n\n",encontrar_pico(array7,4),find_peak(array7,4));

  free(a);

  return 0;
}