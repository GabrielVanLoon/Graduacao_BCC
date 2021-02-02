#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define T 4

int main(void){

    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        printf("Hello World!! From %d/%d\n", id, num_threads);
    }
    return EXIT_SUCCESS;
}