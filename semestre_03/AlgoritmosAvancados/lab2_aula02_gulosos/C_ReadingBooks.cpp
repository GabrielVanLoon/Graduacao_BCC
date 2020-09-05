#include <iostream>
#include <queue> 

using namespace std;

int main(void){

    int n, k, ti, ai, bi;
    long total_time = 0;
    int  k_rest_ana, k_rest_bob;

    priority_queue<int, vector<int>, greater<int>> both;
    priority_queue<int, vector<int>, greater<int>> ana;
    priority_queue<int, vector<int>, greater<int>> bob;

    // Lendo os livros e colocando nas filhas de prioridade.
    scanf("%d %d", &n, &k);
    k_rest_bob = k_rest_ana = k;

    for(int i = 0; i < n; i++){
        scanf("%d %d %d", &ti, &ai, &bi);

        if(ai && bi)
            both.push(ti);
        else if(ai)
            ana.push(ti);
        else if(bi) 
            bob.push(ti);
        // Precisa testar todos os else if rigorosamentes pq há livros que nenhum dos 2 gosta
        // e portanto não faz sentido adicionar na pilha.
    }
    
    // Verifica se há livros suficientes que ambos gostam, senão acaba o problema
    if((both.size()+ana.size() < k) || (both.size()+bob.size() < k)){
        printf("-1\n");
        return 0;
    }

    // Enquanto houver opcoes individuais para bob e ana.
    while(k_rest_bob > 0 || k_rest_ana > 0){
        
        // Se acabou a pilha da ana e ela ainda tem k, precisa tirar do both
        if(ana.empty() && k_rest_ana > 0){
            total_time += both.top();
            both.pop();
            k_rest_ana -= 1;
            k_rest_bob -= 1;
        
        // Idem acima para bob
        } else if(bob.empty() && k_rest_bob > 0){
            total_time += both.top();
            both.pop();
            k_rest_ana -= 1;
            k_rest_bob -= 1;
        
        // Se acabou both mas não acabou o de ana, precisa pega de ana.
        } else if(both.empty() && k_rest_ana > 0){
            total_time += ana.top();
            ana.pop();
            k_rest_ana -= 1;
        
        // Se acabou both mas não acabou bob, precisa pegar de bob
        } else if(both.empty() && k_rest_bob > 0){
            total_time += bob.top();
            bob.pop();
            k_rest_bob -= 1;
        
        } else {
            if(both.top() <= ana.top() + bob.top()){
                total_time += both.top();
                both.pop();
                k_rest_ana -= 1;
                k_rest_bob -= 1;
            } else {
                total_time += ana.top() + bob.top();
                ana.pop(); bob.pop();
                k_rest_ana -= 1;
                k_rest_bob -= 1;
            }
        }

    }

    printf("%ld\n", total_time);
    return 0;

}
