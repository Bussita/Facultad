#include <omp.h>
#include <stdio.h>

int main(){
    int i = 10;
    #pragma omp parallel private(i)
    {
        // variable i is not initialized
        printf("thread %d: i = %d\n", omp_get_thread_num(), i);
        i = 1000;
    }
    printf("private i = %d\n", i);
}