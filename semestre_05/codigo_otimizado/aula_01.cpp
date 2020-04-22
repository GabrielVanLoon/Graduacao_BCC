#include <stdlib.h>
#include <iostream>
#include <time.h>

using namespace std;

// Ferramenta PERF -> Exibe métricas acerca do software utilizado
// e é útil para verificar questões de hardware como cache e branch miss.
//
// sudo perf stat -e L1-dcache-loads,L1-dcache-load-misses './exec 100 100 100'

/** 
    LOOP UNROLLING

    Otimiza, fazendo mais de 1 operação por loop. 
    branches
    branch-misses
    sudo perf stat -e L1-dcache-loads,L1-dcache-load-misses,branches,branch-misses ./exec
*/


int main(int argc, char* argv[]){
    srand(time(NULL));
    int m=1,n=1, k=1;
    cin >> n >> m >> k;

    // Prepara as matrizes
    double** A = (double**) malloc( n * sizeof(double*) );
    double** B = (double**) malloc( m * sizeof(double*) );
    double** C = (double**) malloc( n * sizeof(double*) );
    
    for(int i = 0; i < n; i++)
        A[i] = (double*) malloc( m * sizeof(double) );
    for(int i = 0; i < m; i++)
        B[i] = (double*) malloc( k * sizeof(double) );
    for(int i = 0; i < n; i++)
        C[i] = (double*) calloc( k , sizeof(double) );

    // Lendo as entradas das matrizas
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            A[i][j] = (rand()%1000)/100.00;
            //cin >> A[i][j];
    for(int i = 0; i <m; i++)
        for(int j = 0; j < k; j++)
            B[i][j] = (rand()%1000)/100.00;
            // cin >> B[i][j];

    // MULTIPLICAÇÃO PADRÃO
    for(int i = 0; i < n; i++)
        for(int j = 0; j < k; j++)
            for(int t = 0; t < m; t++)
                C[i][j] += A[i][t] * B[t][j];

    // MULTIPLICAÇÃO OTIMIZADA PARA A CACHE -> APROVEITANDO PRINCIPIO DE LOCALIDADE E DIMINUINDO OS L1-DCACHE-LOAD-MISSES
    // for(int i = 0; i < n; i++)
    //     for(int t = 0; t < m; t++)
    //         for(int j = 0; j < k; j++)
    //             C[i][j] += A[i][t] * B[t][j];

    // MELHORANDO LOOP UNROLING
    // for(int i = 0; i < n; i++)
    //     for(int j = 0; j < k; j++)
    //         for(int t = 0; t < m; t+=2){
    //             C[i][j] += A[i][t]   * B[t][j];
    //             C[i][j] += A[i][t+1] * B[t+1][j];
    //         }
                

    // NAO PRINTARR
    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < k; j++)
    //         cout << C[i][j] << '\t';
    //     cout << endl;
    // }


            
    // Desalocando as matrizes
    for(int i = 0; i < n; i++)
        free(A[i]);
    for(int i = 0; i < m; i++)
        free(B[i]);
    for(int i = 0; i < n; i++)
        free(C[i]);
    free(A);
    free(B);
    free(C);

    return 0;
}