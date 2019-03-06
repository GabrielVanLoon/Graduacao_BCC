/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    Fev/2018
 * Aula 02	Usando Estruturas de Dados II
 * 
 * Pdf da aula: http://www.lcad.icmc.usp.br/~jbatista/scc210/Aula3-STL2.pdf
 */

/** 
 * Exercicio 03 - Argus
 * We have developed a Data Stream Management System called Argus, which processes 
 * the queriesover the data streams. Users can register queries to the Argus. Argus 
 * will keep the queries runningover the changing data and return the results to the 
 * corresponding user with the desired frequency.For the Argus, we use the following 
 * instruction to register a query:
 * 
 *  Register Q_num  Period 
 * 
 * Q_num (0< Q_num < 3000) is query ID-number, and Period (0< Period <3000) is the interval
 * between two consecutive returns of the result. After Period seconds of register, the 
 * result will be returned for the  first time, and after that, the result will be returned 
 * every Period seconds.
 * 
 * Here we have several different queries registered in Argus at once. It is confirmed 
 * that all the queries have different Q_num. Your task is to tell the  first K-queries to 
 * return the results. If two or more queries are to return the results at the same time, 
 * they will return the results one by one in theascending order ofQnum.
 * 
 * Ref.: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3644
 */
#include <iostream>
#include <string>
#include <map>
#include <queue>

using namespace std;

class Task {
    public:
        int id;         // Q_num da tarefa
        int period;     // Periodo da tarefa
        int nextTime;   // Prox. tempo que ela será executada

        Task(int mid, int mperiod){
            this->id = mid;
            this->period = mperiod;
            this->nextTime = mperiod;
        }

        /** 
         * @friend bool operator<(Task const &t1, Task const &t2)
         * Ajusta o operador < para remover tarefas com menor valor de
         * nextTime primeiro. Além disso, utiliza o id como critério de
         * desempate caso haja tarefas simultâneas.
         */
        friend bool operator<(Task const &t1, Task const &t2){
            if(t1.nextTime != t2.nextTime)
                return t1.nextTime > t2.nextTime;
            else
                return t1.id > t2.id;
        }
};

int main(){

    priority_queue<Task> stream;
    int id, period, k;
    string opt;

    // 1ª Etapa - Inserindo as tarefas na Stream
    cin >> opt;
    while(opt[0] != '#'){
        cin >> id >> period;
        stream.push(Task(id,period));

        cin >> opt;
    }

    // 2ª Etapa - Realizar as tasks
    cin >> k;
    while(k > 0 && !stream.empty()){
        // Task a ser executada
        Task t = stream.top();
        stream.pop();
        // Print do id
        cout << t.id << endl;
        // Reinserindo com tempo atualizado
        t.nextTime += t.period; 
        stream.push(t);

        k--;
    }
}
