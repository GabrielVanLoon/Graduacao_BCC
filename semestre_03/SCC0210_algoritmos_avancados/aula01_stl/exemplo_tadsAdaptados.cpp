/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    Fev/2018
 * Aula 01  Estudo de Containers Sequenciais Adaptados
 * Ref.: https://en.cppreference.com/w/cpp/container
 */

/**
 * A Biblioteca Padrão do C++ (STL) implementa os seguintes conteiners 
 * sequenciais adaptados: 
 * 
 * <stack>              adapts a container to provide stack (LIFO data structure) 
 * <queue>              adapts a container to provide queue (FIFO data structure) 
 * <priority_queue>     adapts a container to provide priority queue 
 */
#include <stack>
#include <queue> // implementa queue e priority_queue

// Adicionais
#include <iostream>     // cin, cout
#include <algorithm>    // sort
#include <string> 

using namespace std;

int main(){
     
    /** 
     * stack<class T>
     * Ref. https://en.cppreference.com/w/cpp/container/stack
     */
        stack<string> p;

        p.push("1º Gabriel");
        p.push("2º Mathias");
        p.push("3º Alberto");

        while(!p.empty()){
            cout << p.top() << " | ";
            p.pop();
        }
        cout << endl << endl;

    /** 
     * queue<class T>
     * Ref. https://en.cppreference.com/w/cpp/container/queue
     */
        queue<string> q;

        q.push("1º Gabriel");
        q.push("2º Mathias");
        q.push("3º Alberto");

        while(!q.empty()){
            cout << q.front() << " | ";
            q.pop();
        }
        cout << endl << endl;

    /** 
     * priority_queue<class T>
     * Ref. https://en.cppreference.com/w/cpp/container/priority_queue
     * Func. de comparação padrão tráz do maior para o menor.
     */
        priority_queue<string> pq;

        pq.push("1º Gabriel");
        pq.push("5º Mathias");
        pq.push("2º Alberto");
        pq.push("3º Giovanni");
        pq.push("5º Victor");

        while(!pq.empty()){
            cout << pq.top() << " | ";
            pq.pop();
        }
        cout << endl << endl;

    return 0;
}