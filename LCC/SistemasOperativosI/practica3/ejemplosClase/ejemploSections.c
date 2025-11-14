#include <omp.h>
#include <stdio.h>

int main(){
    #pragma omp parallel
    {

        printf("Hola a todos soy el thread %d\n",omp_get_thread_num());


        #pragma omp sections
        {
            #pragma omp section
            {
                printf("Hello from thread %d (section 1)\n",omp_get_thread_num());
            }
            #pragma omp section
            {
                printf("Hello from thread %d (section 2)\n",omp_get_thread_num());
            }
        }
    }
}