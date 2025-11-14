#include <stdio.h>
#include <omp.h>

int main(){


    #pragma omp parallel shared(x, y) private(x_next, y_next)
    {
    #pragma omp critical ( critical_section1 )
    {
        x_next = dequeue(x);
    }
        work(x_next);
    #pragma omp critical ( critical_section2 )
    {
        y_next = dequeue(y);
    }
        work(y_next);
    }

}