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
    const int tamanhoPop = 50;
    const int tamCoef    = 3;

    Individuo populacao[tamanhoPop];
    Individuo filhos[tamanhoPop];
    
    Individuo melhorIndividuo;
    int       idadeMelhorIndividuo;

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
            printf("\t%f pts - (%.2f\t%.2f\t%.2f)\n", populacao[i].score,  populacao[i].coef[0],  populacao[i].coef[1], populacao[i].coef[2]);
        }
    }

    void cross_suruba_1xTodos(){

        Individuo parent1 = populacao[0];
        int       totalScore, val;

        for(int i = 1; i < tamanhoPop; i++){
            Individuo parent2 = populacao[i];

            totalScore = parent1.score - parent2.score;

            for(int j = 0; j < tamCoef; j++){
                val = rand()%100;
                if(val < 50)
                    filhos[i].coef[j] = parent1.coef[j];
                else 
                    filhos[i].coef[j] = parent2.coef[j];
            }

            populacao[i] = filhos[i];
        } 

    }

    void mutacao(){
        // Aplica a mutacao em todos os filhos e sempre altera 1 dos genes
        for(int i = 1; i < tamanhoPop; i++){
            int c     = rand()%tamCoef;
            int sinal = rand()%2;

            if(sinal == 0)
                populacao[i].coef[c] += 1;
            else 
                populacao[i].coef[c] -= 1;
        }
    }

    void mutacao2(){
        // Essa mutação tem a chance de gerar algum dos genes novamente.
        // Porém atinge apenas 1 dos filhos.
        for(int i = 1; i < tamanhoPop; i++){
            int c     = rand()%tamCoef;
            int rate  = rand()%100;

            if(rate < 30){
                populacao[i].coef[c] = (rand()%2000) - 1000;
            }
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
        printf("\tGeração nº %d\n", contGeracao);
        exibirPopulacao();
        printf("\n");

        // Verifico se o Score do melhor indivíduo ultrapassou o melhor global
        if(populacao[0].score > melhorIndividuo.score){
            melhorIndividuo      = populacao[0];
            idadeMelhorIndividuo = contGeracao;
        }
            

        // 3ª Etapa - Gerar os filhos com os pais atuais
        cross_suruba_1xTodos();

        // 4ª Etapa - Mutação nos genes dos filhos
        mutacao();
        mutacao2();
    }

    printf("\tMELHOR INDIVIDUO NASCEU NA GERAÇÃO %d\n", idadeMelhorIndividuo);
    printf("\t%f pts - (%.2f,%.2f,%.2f)\n", melhorIndividuo.score, melhorIndividuo.coef[0], melhorIndividuo.coef[1], melhorIndividuo.coef[2]);

    return 0;
}