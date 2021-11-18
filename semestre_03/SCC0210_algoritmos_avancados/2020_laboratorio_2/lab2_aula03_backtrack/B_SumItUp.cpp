#include <iostream>
#include <array>
#include <deque>
using namespace std;

int n,t,possibilidades;
int nums[15];
deque<int> utilizados;

void calc_possibilidades(int soma_atual, int i){
    if(soma_atual == t){
        possibilidades += 1;

        printf("%d",utilizados[0]);
        for(int i = 1; i < utilizados.size(); i++){
            printf("+%d",utilizados[i]);
        }printf("\n");
        return;

    } else if(i == n){
        return;
    }
    // pega
    if(nums[i] + soma_atual <= t){
        utilizados.push_back(nums[i]);
        calc_possibilidades(nums[i] + soma_atual, i+1);
        utilizados.pop_back();
    }
    // não pega
    // Pq o next? Pq se houver numeros repetidos eles podem
    // nao ser pegos e gerar somas repetidas como 3+1, 3+1, 3+1
    int next = i+1;
    while(i < n && nums[i] == nums[next])
        next += 1;
    calc_possibilidades(soma_atual, next);
}

int main(void){

    scanf(" %d %d", &t, &n);
    while(t || n){
        // Resetando as variaveis
        possibilidades = 0;
        utilizados.clear();

        // lendo as variaveis
        for(int i = 0; i < n; i++){
            scanf("%d", &nums[i]);
        }
        
        // Calcula as somas
        printf("Sums of %d:\n", t);
        calc_possibilidades(0,0);
        if(possibilidades == 0)
            printf("NONE\n");

        scanf("%d %d", &t, &n);
    }

}