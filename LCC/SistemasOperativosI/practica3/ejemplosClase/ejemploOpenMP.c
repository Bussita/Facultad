#include <stdio.h>
#include <omp.h>

int main(){

    #pragma omp parallel
    {
        int id = omp_get_thread_num(); // thread id
        int nt = omp_get_num_threads();
        printf("Thread id: %d Numero de threads: %d\n",id,nt);
    }

}