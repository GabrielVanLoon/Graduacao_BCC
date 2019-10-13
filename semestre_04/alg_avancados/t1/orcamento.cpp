/**
 * T1 Algoritmos Avançaçdos - Orçamento de Projeto
 * 
 * OBJETIVO: 
 * Minimizar o custo da compra de licenças de um software de forma que 
 * a empresa sempre possua permissão para utilizar a ferramenta durante 
 * o meses que durarem o projeto.
 * 
 * ENTRADAS: 
 * Uma linha com 2 inteiros, N e M,seguida de M linhas com 2 inteiros e 1 n ́umero real, A B X.
 * 
 * N - indica a duração em meses do projeto;
 * M - indica o número de pacotes da licença disponíveis;
 * A B X - indica um pacote disponível no mês A que dura B meses e custa X reais.  
 * 
 * Obs.: Cada mês é representado unicamente por um inteiro de 0 a 11
 * 
 * SAIDA:
 * Custo mínimo para comprar as licenças durante o projeto.
 */
#include <iostream>
#include <vector>
#include <algorithm> 

#define INFINITO 99999.0

// Struct para representar os pacotes
typedef struct _pacote {
    int   ini;
    int   fim;
    float custo;
} Pacote;

// Ordena os pacotes por ordem de fim.
bool compararPacotes(Pacote l, Pacote r){
    return l.fim < r.fim;
}

// VARIÁVEIS PRINCIPAIS
// N - Duração do Projeto em meses.
// M - Qtd. Pacotes disponíveis
// Q - Duração do projeto em Anos (arred. para cima)
// v - Vetor de pacotes disponíveis.
int N, M, Q;
float menorCusto;
std::vector<Pacote> v;
std::vector<float>  memo;

/**
 * Retorna o menor custo para manter o projeto considerando todos
 * os pacotes entre v[0...i]
 */ 
float custo(int i);

/**
 * Busca um pacote entre [0...i] cujo tempo de expiração da licença
 * seja igual ao @param ini e retorna seu indice.
 * Caso não exista retorna o indice -1
 */
int buscarAnterior(int i, int ini);

int main(void){
    
    // 1ª Etapa - Lendo as entradas e criando o vetor de pacotes.
    scanf(" %d %d", &N, &M);
    Q = N/12 + ((N%12 > 0)? 1 : 0); 

    for(int i = 0; i < M; i++){
        int A,B;
        float C;
        scanf(" %d %d %f", &A, &B, &C);

        for(int y = 0; y < Q; y++){
            Pacote p = {A,A+B,C};
            v.push_back(p);

            A += 12; // Atualiza o pacote para o mês 12 == janeiro do 2º ano
            B += 12; // 24 == janeiro 3º ano etc...
        }
    }

    // 2ª Etapa - Ordenando o vetor de pacotes por ordem de término.
    std::sort(v.begin(), v.end(), compararPacotes);

    // 3º Etapa (Opcional) - Gerando vetor de memoização para melhorar o custo do backtracking.
    memo.resize(v.size()+1);
    std::fill(memo.begin(), memo.end(), -1.0);

    // Descomente para visualizar o vetor ordenado...
    printf("\nPacotes Ordenados:\n");
    for(int i = 0; i < v.size(); i++){
        printf("%d %d %.2f\n", v[i].ini, v[i].fim, v[i].custo);
    }
    printf("\n");
    
    // 3ª Etapa - Vamos executar o nosso algoritmo que irá retornar o menor custo
    //            para comprar os pacotes do projeto. 
    menorCusto = INFINITO;
    for(int i = v.size()-1; i >= 0; i--){
        if(v[i].fim < N) break;
        menorCusto = std::min(menorCusto, custo(i));
    }
    std::cout << menorCusto << std::endl;
    
    // Para verificar o vetor de memoização descomente a linha abaixo
    // for(int i = 0; i < v.size(); i++){
    //     printf("%f\t", memo[i]);
    // } printf("\n");

    return 0;
}


float custo(int i){  
    // Descomente para trackear a recursao
    //printf("função %d...\n", i);

    // Caso de parada
    if(i < 0) return 0;
        
    // Caso a sessão atual já tenha sido memorizada
    if(memo[i] > 0){
        return memo[i];

    } else {
        memo[i]  = INFINITO;
        
        // Buscando os pacote anteriores que tal que v[ant].fim == v[i].ini]
        // Salva o valor que minimiza o custo entre o período [0...v[i].fim]
        int anterior;
        anterior = buscarAnterior(i-1, v[i].ini);
        do {
            memo[i] = std::min(memo[i], v[i].custo + custo(anterior));
            anterior = buscarAnterior(anterior-1, v[i].ini);
        } while(anterior != -1);
    }

    return memo[i];
}

int buscarAnterior(int i, int ini){
    // Busca um pacote tal que ant.fim == prox.ini
    // o range da busca ocorre de [0,i) 
    for(; i >= 0; i--){
        if(v[i].fim == ini)
            return i;
        if(v[i].fim < ini)
            return -1;
    }
    return -1;
}

