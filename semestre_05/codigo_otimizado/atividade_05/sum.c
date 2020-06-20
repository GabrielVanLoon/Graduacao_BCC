#include <stdio.h>
#include <x86intrin.h>

#define N 1048576

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
#else
    printf("%f\n", sum_default(v));
#endif
    return 0;
}