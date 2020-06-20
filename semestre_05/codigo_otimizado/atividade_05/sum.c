#include <stdio.h>
#include <x86intrin.h>

#define N (1024*1024)   // tamanho   = 1 MB floats && 1 float = 4 Bytes => 4MB bytes]
                        // L1 Dcache =  64 KBytes -> 16384 floats
                        //              vamos usar blocos de 8192 floats por iteração
#define BLOCK_SIZE 8192

// DEFINE O MODO UTILIZDo
#define INTRINSIC_BLOCK 1

#ifdef INTRINSIC
    float sum_vectorized(float* v){
        int i;
        int jump = 4;
        __m128 v1, v2;
        while(jump != N){
            for(i = 0; i < N; i += 2*jump){
                v1  = _mm_loadu_ps(v+i);
                v2  = _mm_loadu_ps(v+i+jump);
                v1  = _mm_add_ps(v1, v2);
                _mm_store_ps(v+i, v1);
            }
            jump = 2*jump;
        }
        v1 = _mm_loadu_ps(v);
        v1 = _mm_hadd_ps(v1, v1);
        v1 = _mm_hadd_ps(v1, v1);
        _mm_store_ss(v, v1);

        return v[0];
    }
    
#elif INTRINSIC_BLOCK
    float sum_vectorized(float* v, int size){
        int i;
        int jump = 4;
        __m128 v1, v2;
        while(jump != size){
            for(i = 0; i < size; i += 2*jump){
                v1  = _mm_loadu_ps(v+i);
                v2  = _mm_loadu_ps(v+i+jump);
                v1  = _mm_add_ps(v1, v2);
                _mm_store_ps(v+i, v1);
            }
            jump = 2*jump;
        }
        v1 = _mm_loadu_ps(v);
        v1 = _mm_hadd_ps(v1, v1);
        v1 = _mm_hadd_ps(v1, v1);
        _mm_store_ss(v, v1);

        return v[0];
    }

    float sum_blocks(float* v){
        // Divide o vetor V em blocos de tal forma que o mesmo caiba completamente
        // na memória cache L1.
        float soma = 0;
        for(int block = 0; block < N; block += BLOCK_SIZE){
            soma += sum_vectorized(v+block, BLOCK_SIZE);
        }
        return soma;
    }

#else
    float sum_default(float* v){
        int i; 
        float sum = 0;
        for(i = 0; i < N; i++){
            sum += v[i];
        }
        return sum;
    }
#endif

int main(){
    int i;
    float v[N];
    for(i = 0; i < N; i++){
        v[i] = 1;
    }

#ifdef INTRINSIC
    printf("%f\n", sum_vectorized(v));   
#elif INTRINSIC_BLOCK
    printf("%f\n", sum_blocks(v));   
#else
    printf("%f\n", sum_default(v));
#endif

    return 0;
}