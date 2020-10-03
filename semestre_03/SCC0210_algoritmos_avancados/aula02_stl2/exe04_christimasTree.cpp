/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    Fev/2018
 * Aula 02	Usando Estruturas de Dados II
 * 
 * Pdf da aula: http://www.lcad.icmc.usp.br/~jbatista/scc210/Aula3-STL2.pdf
 */

/** 
 * Exercicio 04 - Tom's Christmas
 * It’s finally christmas and Tom has been waiting for Santa Claus all year! 
 * This year he was a good boy and he won a load of presents.There were ​'m' boxes 
 * under his tree, but Santa Claus surprised him, and some boxes have other boxes
 * inside them. So a box has either other boxes inside it or a toy. All boxes have
 * different sizes, but Tom likes big boxes, so the first present he will open will
 * be the largest, and after opening somebox '​i'​, he will choose the largest between
 * the presents he had before opening '​i' and the ones revealed by ​'i'​.
 * 
 * However, there are many boxes, and after opening '​k' presents Tom will get tired.
 * Findout how many toys did Tom get before he got tired.
 */
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <array>

#define SIZE 100001
using namespace std;

int main(){

    int n; // nº de Presentes (Máx 10^5)
    int m; // nº de Caixas
    int k; // Qtd. Caixas abertas
    int qtdBrinquedos = 0; // Brinquedos achados por Tom
    cin >> n >> m >> k;

    // Tamanhos das caixas 
    array<int,SIZE>      tamanhos;
    for(int i = 1; i <= n; i++){
        int temp;
        cin >> temp;
        tamanhos[i] = temp;
    }

    // Mapeando o que há dentro de cada caixa
    // Caso vazia, então há um brinquedo dentro.
    vector<int> caixas[SIZE];
    for(int i = 1; i <= n; i++){
        int qtd; 
        cin >> qtd;
        for(int j = 0; j < qtd; j++){
            int indexSub; 
            cin >> indexSub;
            caixas[i].push_back(indexSub);
        }
    }

    // Priority Queue irá salvar as caixas disponívels para ser
    // aberta debaixo na árvore, e também inserir caixas que forem 
    // abertas com o tempo.
    priority_queue<pair<int,int>> arvore; // pair<Tamanho, id>
    
    for(int i = 0; i < m; i++){
        int idCaixa;
        cin >> idCaixa;
        arvore.push(pair<int,int>(tamanhos[idCaixa],idCaixa));
    }

    // Abrindo as caixas
    for(int i = 0; i < k; i++){
        pair<int,int> at = arvore.top();
        arvore.pop(); 

        // 1º Caso: Achou um brinquedo
        if(caixas[at.second].empty()){
            qtdBrinquedos++;

        // 2ª Caso: Adiciona as subcaixas na árvore
        } else {
            vector<int>::iterator it;
            for(it = caixas[at.second].begin(); it != caixas[at.second].end(); it++)
                arvore.push(pair<int,int>(tamanhos[*it],*it)); 
        }
    }

    cout << qtdBrinquedos << endl;
}
