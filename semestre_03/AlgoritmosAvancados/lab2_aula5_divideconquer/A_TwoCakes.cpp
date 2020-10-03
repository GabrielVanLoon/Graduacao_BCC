#include <iostream>

using namespace std;

int n,a,b;
int min_cakes, max_cakes, max_min;

int main(void){

    // Lendo qtd pessoas, pedacos bolo A, pedacos bolo B
    scanf(" %d %d %d", &n, &a, &b);
    max_min = 1;

    // N divisoes de quem come A e quem come B
    for(int i = 1; i <= n-1; i++){
        int min_a = a/i;
        int min_b = b/(n-i);

        if(min_a == 0 || min_b == 0)
            continue;

        max_min = max(max_min, min(min_a,min_b));
    }


    printf("%d", max_min);
}

// Tentativa incorreta: Nao percebi que tinha a restrição de TODOS os bolos terem
// de ser servidos.
// int main(void){

//     // Lendo qtd pessoas, pedacos bolo A, pedacos bolo B
//     scanf(" %d %d %d", &n, &a, &b);
//     min_cakes = 1; 
//     max_cakes = min(a,b);
//     max_min = 1;

//     while(min_cakes <= max_cakes){
//         int pedacos   = (min_cakes+max_cakes)/2;
//         int a_pessoas = a/pedacos;
//         int b_pessoas = b/pedacos;

//         int a_resto = a%pedacos;
//         int b_resto = b%pedacos;

//         // Se serve mais pessoas do que precisa, tenta aumentar a carga
//         if(a_pessoas+b_pessoas >= n){
//             min_cakes = pedacos+1;
//             max_min = pedacos;
//         } else {
//             max_cakes = pedacos-1;
//         } 
//     }

//     printf("%d", otimo);
    
// }