/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    Fev/2018
 * Aula 01	Usando Estruturas de Dados
 */

/** 
 * Exercicio 02 
 * Queues and Priority Queues are data structures which are known to 
 * most computer scientists. The Team Queue, however, is not so well known, 
 * though it occurs often in everyday life. At lunch time thequeue in front 
 * of the Mensa is a team queue, for example.
 * 
 * In a team queue each element belongs to a team. If an element enters the 
 * queue, it first searches thequeue from head to tail to check if some of 
 * its teammates(elements of the same team) are already in thequeue. If yes, 
 * it enters the queue right behind them. If not, it enters the queue at the 
 * tail and becomesthe new last element (bad luck). Dequeuing is done like in 
 * normal queues: elements are processed fromhead to tail in the order they appear 
 * in the team queue.
 * 
 * Your task is to write a program that simulates such a team queue.
 * 
 * Obs. Foi implementado o Team Queue utilizando uma lista de listas.
 */
#include <iostream>
#include <string>
#include <list>
#include <unordered_map>

using namespace std;

int main(){
    
    int numTeste = 1, qtdTimes;

    cin >> qtdTimes;
    while(qtdTimes != 0){
        cout << "Scenario #" << numTeste++ << endl;

        list<list<int>>         teamQ;
        unordered_map<int, int> times;
        string                  opt;
        int                     aux;

        // Mapeando os integrantes de cada time.
        for(int i = 0; i < qtdTimes; i++){
            int n;
            cin >> n;
            for(int j = 0; j < n; j++){
                cin >> aux;
                times.insert(pair<int,int>(aux, i));
            }
        }

        // Executando as entradas e saídas
        cin >> opt;
        while(opt.compare("STOP") != 0){
            
            if(opt.compare("ENQUEUE") == 0){
                cin >> aux; // Valor a ser inserido

                list<list<int>>::iterator   it;
                bool                        inseriu = false;
                
                // Buscando se o time já está na fila.
                for(it = teamQ.begin(); it != teamQ.end(); it++){
                    // cout << "Time do valor inserido: " << times[aux] << endl;
                    // cout << "Time valor atual: "       << times[it->front()] << endl;
                    
                    if(times[aux] == times[it->front()]){
                        it->push_back(aux);
                        inseriu = true;
                        break;
                    }
                }

                // Caso não existe, cria um novo time e insere na fila
                if(inseriu == false){
                    list<int> novoTime;
                    novoTime.push_back(aux);
                    teamQ.push_back(novoTime);
                }
                
            } else {
                if(!teamQ.empty()){
                    cout << teamQ.front().front() << endl;
                    teamQ.front().pop_front();
                    if(teamQ.front().empty()) teamQ.pop_front();
                }
            }
            
            cin >> opt;
        }

        // Quebra de linha entre os testes.
        cout << endl;
        
        //Qtd. times no próx teste.
        cin >> qtdTimes;
    }

	return 0;
}
