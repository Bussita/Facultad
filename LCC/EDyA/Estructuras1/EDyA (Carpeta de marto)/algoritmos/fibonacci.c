#include <stdio.h>

int recursive_fibonacci(int n);

int DP_fibonacci(int n); 

int DP_fibonacci_aux();

int DP2_fibonacci(int n);


int main(void) {



  return 0;
}


int DP_fibonacci(int n) {


}


int DP_fibonacci_aux() {



}


// Not optimal, because it repets many operations
int recursive_fibonacci(int n) {

  if (n == 0)
    return 0;
  
  if (n == 1)
    return 1;

  return recursive_fibonacci(n - 1) + recursive_fibonacci(n - 2);
}


int DP2_fibonacci(int n) {

  int fib[2] = {0,1};

  for (int i = 0 ; )


}5