#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

/**
 * Typedef Indivíduo
 */ 
typedef struct _ind{
    float   coef[3];   // Coeficientes
    float   score;    // Pontos de fitness
} Individuo;

//bool compararInd(Individuo lhs, Individuo rhs) { 
//    return lhs.score < rhs.score; // Ordena crescente
//}

bool compararInd(Individuo lhs, Individuo rhs) { 
   return lhs.score > rhs.score; // Ordena decrescente
}

/**
 * Variáveis importantes para o algoritmo
 */
    const int tamanhoPop = 10;
    Individuo populacao[tamanhoPop];
    Individuo melhorIndividuo;

    int       contGeracao;
    
/**
 * Funções importantes
 */
    int iniciarPopulacao(){
        srand(time(NULL));

        for(int i = 0; i < tamanhoPop; i++){
            for(int k = 0; k < 3; k++){
                populacao[i].coef[k] = (rand()%2000) - 1000;
            }
        }
    }

    float calcularFitness(Individuo* x){
        // f(x) = café OU f(x) = 20-café
        return  (x->coef[1] <= 10.0) ? x->coef[1] : 20.0 - x->coef[1];
    }

    void exibirPopulacao(){
        for(int i = 0; i < tamanhoPop; i++){
            printf("\t%f pts - (-, %f, -)\n", populacao[i].score, populacao[i].coef[1]);
        }
    }


int main(void){

    // 1ª Etapa - Iniciando a população
    iniciarPopulacao();

    // Loop de Gerações
    for(contGeracao = 1; contGeracao <= 100; contGeracao++){

        // 2ª Etapa - Calcular o fitness da população
        for(int i = 0; i < tamanhoPop; i++)
            populacao[i].score = calcularFitness(&populacao[i]);

        // Ordeno a população por meio de seus scores.
        sort(populacao, populacao+10, compararInd);
        exibirPopulacao();


        break;


    }

    return 1;
}