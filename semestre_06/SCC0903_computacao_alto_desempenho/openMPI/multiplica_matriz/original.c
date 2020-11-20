#include <stdio.h>
#include <stdlib.h>

double** aloca_matriz(int N) {
	double **matriz = (double**) malloc(N*sizeof(double*));
	for (int i = 0; i < N; i++)
	{
		matriz[i] = (double*) malloc(N*sizeof(double));
	}

	return matriz;
}

int main() {
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

	double** matrizR1 = aloca_matriz(N);
	double** matrizR2 = aloca_matriz(N);
	double aux = 0;

	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {			
			matrizR1[i][j] = 0;
			for(int k = 0; k < N; k++) {
				aux +=  matrizA[i][k] * matrizB[k][j];
			}
			matrizR1[i][j] = aux;
			aux = 0;
		}
	}

	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {			
			matrizR2[i][j] = 0;
			for(int k = 0; k < N; k++) {
				aux +=  matrizC[i][k] * matrizD[k][j];
			}
			matrizR2[i][j] = aux;
			aux = 0;
		}
	}

	double** matrizRF = aloca_matriz(N);

	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			matrizRF[i][j] = matrizR1[i][j] + matrizR2[i][j];
		}
	} 

	int j = 0; 
	for(int i = 0; i < N; i++) {
		for(j = 0; j < (N-1); j++) {
			printf("%.1lf ", matrizRF[i][j]);
		}
		printf("%.1lf\n", matrizRF[i][j]);
	} 


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
		free(matrizR1[i]);
	}
	for(int i = 0; i < N; i++) {
		free(matrizR2[i]);
	}
	for(int i = 0; i < N; i++) {
		free(matrizRF[i]);
	}
    
	free(matrizA);
	free(matrizB);
	free(matrizC);
	free(matrizD);
	free(matrizR1);
	free(matrizR2);
	free(matrizRF);
}