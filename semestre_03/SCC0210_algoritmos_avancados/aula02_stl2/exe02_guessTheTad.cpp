/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    Fev/2018
 * Aula 02	Usando Estruturas de Dados II
 * 
 * Pdf da aula: http://www.lcad.icmc.usp.br/~jbatista/scc210/Aula3-STL2.pdf
 */

/** 
 * Exercicio 02 - I Can Guess the Data Structure!
 * There is a bag-like data structure, supporting two operations:
 *      1 - Throw an element x into the bag.
 *      2 - Take out an element from the bag.
 * Given a sequence of operations with return values, you’re going to guess 
 * the data structure. It is a stack (Last-In, First-Out), a queue (First-In, First-Out), 
 * a priority-queue (Always take out largerelements first) or something else that you can 
 * hardly imagine!
 * 
 * Ref.: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3146
 */
#include <iostream>
#include <string>
#include <stack>
#include <queue>

using namespace std;

int main(){

    // Qtd. de linhas por teste (Máx 10^3).
    int n; 
    
    while(cin >> n){
        int opt, aux;
        bool isS = true, isQ = true, isPQ = true;
        
        stack<int> s;
        queue<int> q;
        priority_queue<int> pq;
        
        // Lendo as entradas e saidas
        for(int i = 0; i < n; i++){
            cin >> opt >> aux;

            if(opt == 1){
                s.push(aux);
                q.push(aux);
                pq.push(aux);
            } else {
                
                // Corner case: Remover nas TAD's vazias
                if(s.empty()){
                   isS = isQ = isPQ = false;
                } else {
                    if(aux != s.top()) isS = false;
                    s.pop();

                    if(aux != q.front()) isQ = false;
                    q.pop();

                    if(aux != pq.top()) isPQ = false;
                    pq.pop();
                }
            }
        }

        // Resposta do problema
        if(!isS && !isQ && !isPQ)
            cout << "impossible" << endl;
        else if(isS && !isQ && !isPQ)
            cout << "stack" << endl;
        else if(!isS && isQ && !isPQ)
            cout << "queue" << endl;
        else if(!isS && !isQ && isPQ)
            cout << "priority queue" << endl;
        else
            cout << "not sure" << endl;
    }

}
