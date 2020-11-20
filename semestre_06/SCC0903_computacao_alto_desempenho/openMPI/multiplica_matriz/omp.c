#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

double** aloca_matriz(int N) {
	double **matriz = (double**) malloc(N*sizeof(double*));
	for (int i = 0; i < N; i++)
	{
		matriz[i] = (double*) malloc(N*sizeof(double));
	}

	return matriz;
}

int main(){

    int N;
	scanf("%d", &N);

	double** matrizA = aloca_matriz(N);
	double** matrizB = aloca_matriz(N);
	double** matrizC = aloca_matriz(N);
	double** matrizD = aloca_matriz(N);

	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			//printf("entrou na leitura");
			scanf("%lf", &matrizA[i][j]);
		}
	}
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {

			//printf("entrou na leitura");
			scanf("%lf", &matrizB[i][j]);
		}
	}
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			scanf("%lf", &matrizC[i][j]);
		}
	}
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			scanf("%lf", &matrizD[i][j]);
		}
	}

    double** matrizG = aloca_matriz(N);
    double** matrizH = aloca_matriz(N);
    double** matrizE = aloca_matriz(N);
	double aux = 0;
	double t = omp_get_wtime();

    int i = 0, j = 0, k = 0, l = 0;
    double soma_parcial = 0;

    #pragma omp parallel shared(matrizA, matrizB, matrizC, matrizD, matrizG, matrizH) private(soma_parcial)
    {
        #pragma omp for collapse(3)  
        for(l = 0; l < 2; l++){
            for(i = 0; i < N; i++) {
                for(j = 0; j < N; j++) {
                    soma_parcial = 0;

                    #pragma omp parallel for reduction(+:soma_parcial)
                    for(k = 0; k < N; k++) {
                        if(l == 0){
                            soma_parcial += matrizA[i][k] * matrizB[k][j];
                        }
                        else{
                            soma_parcial += matrizC[i][k] * matrizD[k][j];
                        }
                    }   

                    if(l == 0) matrizG[i][j] = soma_parcial;
                    else matrizH[i][j] = soma_parcial;
                }
            }
        }

        #pragma omp for collapse(2)
        for(i = 0; i < N; i++){
            for(j = 0; j < N; j++){
                matrizE[i][j] = matrizG[i][j] + matrizH[i][j];
            }
        }
    }

	t = omp_get_wtime() - t;

    

	for(int i = 0; i < N; i++) {
		for(j = 0; j < (N-1); j++) {
			printf("%.1lf ", matrizE[i][j]);
		}
		printf("%.1lf\n", matrizE[i][j]);
	} 

    printf("Tempo: %lf\n", t);

	for(int i = 0; i < N; i++) {
		free(matrizA[i]);
	}
	for(int i = 0; i < N; i++) {
		free(matrizB[i]);
	}
	for(int i = 0; i < N; i++) {
		free(matrizC[i]);
	}
	for(int i = 0; i < N; i++) {
		free(matrizD[i]);
	}
    for(int i = 0; i < N; i++) {
		free(matrizG[i]);
	}
    for(int i = 0; i < N; i++) {
		free(matrizH[i]);
	}
	for(int i = 0; i < N; i++) {
		free(matrizE[i]);
	}
    
	free(matrizA);
	free(matrizB);
	free(matrizC);
	free(matrizD);
    free(matrizG);
    free(matrizH);
	free(matrizE);

    return 0;
}