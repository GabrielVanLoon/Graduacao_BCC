#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main(){

    int N;
    scanf(" %d", &N);

    do {
        while(true){
     
            stack<int>  garagem;
            vector<int> ordem;
            int temp = 0, stop = 0;

            // Lendo a ordem desejada
            for(int i = 0; i < N; i++){
                scanf(" %d", &temp);
                if(i == 0 && temp == 0){
                    printf("\n");
                    stop = 1; 
                    break; 
                }
                ordem.push_back(temp);
            }

            if(stop) break;

            // Verificando se é possível ou não
            int n = 1; // representa os vagões chegando
            int i = 0; // representa o indice atual da ordem
            int s = 0; // representa quantos vagões foram enviados

            while(n <= N+1){
                if( !garagem.empty() && garagem.top() == ordem[i]){
                    garagem.pop();
                    i++;
                    s++;
                } else if (n <= N) {
                    garagem.push(n);
                    n++;
                } else {
                    break;
                }
            }

            if(s == N){
                printf("Yes\n");
            } else {
                printf("No\n");
            }
        }

        scanf(" %d", &N);
    } while(N != 0);

    return 0;

}