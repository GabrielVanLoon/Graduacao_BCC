#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define T 4

typedef struct _sample{
    double  *value;
    double  avg, avg_harmonic, medium, mode, var, std, coef_var;
    int     size;
} sample;

int compare(const void *a, const void *b) {
   return ( *(double*)a - *(double*)b );
}

// Métricas: Média Geométrica e Harmônica
void calc_avg(sample* smp){
    smp->avg          = 0.0;
    smp->avg_harmonic = 0.0;
    
    for(int i = 0; i < smp->size; i++){
        smp->avg += smp->value[i];
        smp->avg_harmonic += 1.0/smp->value[i];
    }
    
    smp->avg = smp->avg/(double)smp->size;
    smp->avg_harmonic = (double)smp->size/smp->avg_harmonic;
}

// Métrica: Moda
void calc_mode(sample* smp){ 
    double mode      = -1;
    int    mode_freq = 0, new_mode_freq = 0;

    for(int i = 1; i < smp->size; ++i) {

        if(smp->value[i] == smp->value[i-1]) {
            new_mode_freq++;
        } else {
            new_mode_freq = 0;
        }

        // Update mode
        if(new_mode_freq > mode_freq) {
            mode_freq = new_mode_freq;
            mode      = smp->value[i];
        }
    }

    smp->mode = mode;
}

// Metrica: Mediana
void calc_medium(sample* smp){ 
    int n = smp->size;
    
    if(n % 2 == 0) {
        smp->medium = (smp->value[n/2-1] + smp->value[n/2]) / 2.0;
    } else {
        smp->medium = smp->value[(int)ceil(n/2)];
    }
}

// Métrica: Variancia, Desvio e Coeficiente
void calc_var_std(sample* smp){ 
    smp->var = 0.0;

    for(int i = 0; i < smp->size; i++){
        smp->var += (smp->value[i] - smp->avg) * (smp->value[i] - smp->avg); 
    }
    smp->var = smp->var/((double) smp->size-1); 
    smp->std = sqrt(smp->var);
    smp->coef_var = smp->std / smp->avg;
}

int main(int argc, char *argv[]){

    // Lendo as medidas da matriz
    int N_SAMPLES, SAMPLE_SIZE;
    scanf(" %d %d", &SAMPLE_SIZE, &N_SAMPLES);

    // Iniciando o vetor e alocando o espaço das amostras
    sample samples[N_SAMPLES];
    for(int i = 0; i < N_SAMPLES; i++){
        samples[i].value = (double*) malloc(SAMPLE_SIZE * sizeof(double));
        samples[i].size  = SAMPLE_SIZE;
    }

    // Fazendo a leitura dos valores
    for(int i = 0; i < SAMPLE_SIZE; i++){
        for(int j = 0; j < N_SAMPLES; j++){
            scanf("%lf", &samples[j].value[i]);
        }
    }

    double wtime = omp_get_wtime();

    // Tudo pronto para entrar na região paralela
    #pragma omp parallel num_threads(T)
    {   
        // Metrics: AVG, HARMONIC AVG 
        #pragma omp single nowait
        {
            for(int i = 0; i < N_SAMPLES; i++){
                #pragma omp task shared(samples) firstprivate(i)
                calc_avg(&samples[i]);
            }
        }
        #pragma omp taskwait

        // Metrics: None - Sorting Values
        #pragma omp single nowait
        {
            for(int i = 0; i < N_SAMPLES; i++){
                #pragma omp task firstprivate(i)
                qsort(samples[i].value, samples[i].size, sizeof(double), compare);
            }
        }
        #pragma omp taskwait

        // Metrics: Mode, Medium
        #pragma omp single nowait
        {
            for(int i = 0; i < N_SAMPLES; i++) {
                #pragma omp task firstprivate(i)
                {
                    calc_mode(&samples[i]);
                    calc_medium(&samples[i]);
                }
                #pragma omp task firstprivate(i)
                calc_var_std(&samples[i]);
            }
        }
    }

    wtime = omp_get_wtime() - wtime;

    // Exibindo as métricas
    printf("Média aritimética: ");
    for(int i = 0; i < N_SAMPLES; i++) printf("%.1lf, ", samples[i].avg);
    printf("\n");

    printf("Média harmônica: ");
    for(int i = 0; i < N_SAMPLES; i++) printf("%.1lf, ", samples[i].avg_harmonic);
    printf("\n");

    printf("Mediana: ");
    for(int i = 0; i < N_SAMPLES; i++) printf("%.1lf, ", samples[i].medium);
    printf("\n");

    printf("Moda: ");
    for(int i = 0; i < N_SAMPLES; i++) printf("%.1lf, ", samples[i].mode);
    printf("\n");

    printf("Variância: ");
    for(int i = 0; i < N_SAMPLES; i++) printf("%.1lf, ", samples[i].var);
    printf("\n");

    printf("Desvio Padrão: ");
    for(int i = 0; i < N_SAMPLES; i++) printf("%.1lf, ", samples[i].std);
    printf("\n");

    printf("Coeficiente de variação: ");
    for(int i = 0; i < N_SAMPLES; i++) printf("%.1lf, ", samples[i].coef_var);
    printf("\n");

    printf("Elapsed time = %.5f\n\n", wtime);

    // Desalocando o espaço das amostras
    for(int i = 0; i < N_SAMPLES; i++){
        free(samples[i].value);
        samples[i].value = NULL;
    }

    return 0;
}