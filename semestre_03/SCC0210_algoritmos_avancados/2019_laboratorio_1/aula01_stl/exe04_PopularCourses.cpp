/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    Fev/2018
 * Aula 01	Usando Estruturas de Dados
 */

/** 
 * Exercicio 04 
 * The input consists of several test cases followed by a line containing `0'. 
 * Each test case begins withan integer 1 < n < 10000, the number of frosh. For 
 * each frosh, a line follows containing the coursenumbers of five distinct 
 * courses selected by the frosh. Each course number is an integer between 
 * 100 and 499.The popularity of a combination is the number of frosh selecting 
 * exactly the same combinationof courses. A combination of courses is considered 
 * most popularif no other combination has higherpopularity.
 */
#include <iostream>
#include <queue>
#include <unordered_set>

using namespace std;

int main(){
    
    int n, aux;
    
    cin >> n;
    while(n != 0){

        // Salva todas as combinacoes de cursos
        unsigned int maiorTurma = 0, empates = 0;
        unordered_multiset<unsigned long int> combinacoes;
        
        // Recebendo as combinacoes de cada aluno
        for(int i = 0; i < n; i++){
            unsigned long int comb = 0;
            unsigned long int ordem = 1;  
            priority_queue<int> cursos;
            
            for(int j = 0; j < 5; j++){
                cin >> aux; 
                cursos.push(aux);
            }
            
            // Recebe os cursos em ordem decrescente e 
            // concatena em um único valor unsigned long.
            while(!cursos.empty()){
                comb += cursos.top() * ordem;
                cursos.pop();
                ordem *= 1000;
            }

            // cout << "Combinação Gerada: " << comb << endl; 
            combinacoes.insert(comb);
            
            // Caso 1: Combinação empatou com a atual
            if(combinacoes.count(comb) == maiorTurma){
                empates++;

            // Caso 2: Há uma nova combinação com mais alunos
            } else if(combinacoes.count(comb) > maiorTurma){
                maiorTurma  = combinacoes.count(comb);
                empates     = 1;
            }  
        }

        cout << maiorTurma * empates << endl;
        
        // Tamanho do proximo caso de teste
        cin >> n;
    }

	return 0;
}
