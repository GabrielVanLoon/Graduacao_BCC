#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define T 4
#define FX(x) (4.0/(1.0+x*x))


int main(void){

    // Seting default number of threads
    omp_set_num_threads(T);

    //Integration limits
    double a = 0.0; 
    double b = 1.0;
    int    n = 1000000000;
    double h = (b-a)/(double)n;
    double total_sum = 0.0;

    #pragma omp parallel for reduction(+:total_sum)
    for(int i = 0; i < n; i++){
        double x   = a + (i + 0.5) * h;
        total_sum += FX(x) * h;
    }

    // Print total sum
    printf("Total Sum is %0.8lf.\n", total_sum);
    printf("Correct value is %0.8lf.\n", 3.14159265358979323846);

    return EXIT_SUCCESS;
}