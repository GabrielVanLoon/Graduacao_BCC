#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <math.h>

using namespace std;

typedef struct _ind{
    float   coef[3];   // Coeficientes
    float   score;    // Pontos de fitness
} Individuo;

/**
 * Variáveis importantes para o algoritmo
 */
    const int tamanhoPop   = 100;
    const int tamCoef      = 3;
    const int rangeInit    = 2000; // -rangeInit <= coef <= rangeInit
    
    // Configurando a taxa de mutação.
    const int   rangeMutacao    = 1000;  // range/divRange 
    const float divRangeMutacao = 100.0; 
    float       rangeMultiply   = 1.0;
    int         contEstagnada   = 0;

    const int maxGeracoes     = 400; 
    const int geracaoGenocida = 50;

    Individuo populacao[tamanhoPop];
    Individuo filhos[tamanhoPop];
    
    Individuo melhorIndividuo;
    int       idadeMelhorIndividuo;
    float     avgScore;  

    int       contGeracao;

/**
 * Typedef Indivíduo
 */ 

    bool compararInd(Individuo lhs, Individuo rhs) { 
        return lhs.score > rhs.score; // Ordena decrescente
    }

/**
 * Funções importantes
 */
    float gerarCoef(){
        return (rand()%(2*rangeInit))-rangeInit;
    }


    int iniciarPopulacao(){
        srand(time(NULL));
        for(int i = 0; i < tamanhoPop; i++){
            for(int k = 0; k < 3; k++){
                populacao[i].coef[k] = gerarCoef();
            }
        }
    }

    int genocidioPopulacao(){
        for(int i = 3*(tamanhoPop/4); i < tamanhoPop; i++){
            for(int k = 0; k < 3; k++){
                populacao[i].coef[k] = gerarCoef();
            }
        }
    }

    float calcularFitness(Individuo* i){
        float x = i->coef[0];
        float y = i->coef[1];
        float z = i->coef[2];
        // f(x) = café OU f(x) = 20-café
        // return  (x <= 10.0) ? x : 20.0 - x;

        // f(x,y,z) = xcos(y) - xsin(z)
        // return x->coef[0]*cos(x->coef[1]) - x->coef[0]*sin(x->coef[2]); 

        // Senoide doida
        return 2*cos(0.39*x) + 5*sin(0.5*x) + 0.5*cos(0.1*x) + 10*sin(0.7*x) + 5*sin(1*x) + 5*sin(0.35*x);

        // Função de duas variaiveis e achar um ponto plano
        //return -fabs( (x*x*y)-(2.0*x*y*y)+(3.0*x*y)+4.0 );
    
    }

    void exibirPopulacao(int onlyBest){
        for(int i = 0; i < tamanhoPop; i++){
            printf("(%.2f  %.2f  %.2f)\n", populacao[i].coef[0],  populacao[i].coef[1], populacao[i].coef[2]);
            if(onlyBest) 
                break;
        }
    }

    void cross_BestxTodos(){

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

    void cross_TorneioDe2(){
        int totalScore, val, p1, p2;

        for(int i = 1; i < tamanhoPop; i++){
            p1 = rand()%tamanhoPop;
            p2 = rand()%tamanhoPop;   
            Individuo parent1 = (populacao[p1].score > populacao[p2].score) ? populacao[p1] : populacao[p2];
           
            p1 = rand()%tamanhoPop;
            p2 = rand()%tamanhoPop;
            Individuo parent2 = (populacao[p1].score > populacao[p2].score) ? populacao[p1] : populacao[p2];

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
            int coef   = rand()%tamCoef;
            int sinal  = rand()%2;
            int change = rand()%(rangeMutacao);

            if(sinal == 0)
                populacao[i].coef[coef] += rangeMultiply*(change/divRangeMutacao);
            else 
                populacao[i].coef[coef] -= rangeMultiply*(change/divRangeMutacao);

            if(populacao[i].coef[coef] < -rangeMutacao ||  rangeMutacao < populacao[i].coef[coef])
                populacao[i].coef[coef] = gerarCoef();
        }
    }


int main(void){

    // 1ª Etapa - Iniciando a população
    iniciarPopulacao();

    printf("epoca;best;avg\n");

    // Loop de Gerações
    for(contGeracao = 1; contGeracao <= maxGeracoes; contGeracao++){

        // 2ª Etapa - Calcular o fitness da população
        for(int i = 0; i < tamanhoPop; i++)
            populacao[i].score = calcularFitness(&populacao[i]);

        // Ordeno a população por meio de seus scores.
        sort(populacao, populacao+10, compararInd);
        // printf("\tGeração nº %d\n", contGeracao);
        // exibirPopulacao(1);
        // printf("\n");

        avgScore = 0;
        for(int i = 0; i < tamanhoPop; i++)
            avgScore += populacao[i].score;
        avgScore = avgScore / tamanhoPop;
        
        // Exibindo tabeladamente os resultados
        printf("%d;%.3f;%.3f\n", contGeracao, populacao[0].score, avgScore);

        // Verifico se o Score do melhor indivíduo ultrapassou o melhor global
        if(populacao[0].score > melhorIndividuo.score){
            melhorIndividuo      = populacao[0];
            idadeMelhorIndividuo = contGeracao;
            rangeMultiply  = 1;
        } else {
            contEstagnada++; 
        }

        // Se a população não evolui faz muito tempo, aumenta a taxa de mutação em 10x
        if(contEstagnada == 5){
            rangeMultiply *= 10;
            contEstagnada  = 0;
        }

        // 3ª Etapa - Gerar os filhos com os pais atuais
        // cross_BestxTodos();
        cross_TorneioDe2();

        // 4ª Etapa - Mutação nos genes dos filhos
        mutacao();

        // Caso seja época de genocidio reseta todos os 25% piores
        if(contGeracao % geracaoGenocida == 0 && rangeMultiply == 1){
            // genocidioPopulacao();
        }
        
    }

    printf("\tMELHOR INDIVIDUO NASCEU NA GERAÇÃO %d\n", idadeMelhorIndividuo);
    printf("\t%f pts - (%.2f,%.2f,%.2f)\n", melhorIndividuo.score, melhorIndividuo.coef[0], melhorIndividuo.coef[1], melhorIndividuo.coef[2]);

    return 0;
}