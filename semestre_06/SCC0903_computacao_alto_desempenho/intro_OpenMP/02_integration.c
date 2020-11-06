#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define T 4
#define FX(x) (4.0/(1+x*x))


int main(void){

    // Seting default number of threads
    omp_set_num_threads(T);

    //Integration limits
    double a = 0.0; 
    double b = 1.0;
    int    n = 100000000;
    double h = (b-a)/n;
    double total_sum = 0.0;

    #pragma omp parallel
    {   
        // Thread details
        int id          = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        // Get integration range
        int    n_per_thread = n/num_threads;
        double a_i          = a + (h*n_per_thread*id);
        double local_sum    = 0.0;
        
        // If division is not exact, put overhead in the last thread
        if(id == num_threads-1 && n % num_threads != 0)
            n_per_thread += n % num_threads;

        // Calc the sum
        for(int i = 0; i < n_per_thread; i++){
            local_sum += FX(a_i) * h;
            a_i       += h;
        }
        printf("Local Sum from %d/%d is %0.8lf.\n", id, num_threads, local_sum);

        // Soma total - Região Crítica
        #pragma omp atomic
        total_sum += local_sum;

        // Obs: Cuidado com problemas de False Sharing
    }

    // Print total sum
    printf("Total Sum is %0.8lf.\n", total_sum);
    printf("Correct value is %0.8lf.\n", 3.14159265358979323846);

    return EXIT_SUCCESS;
}