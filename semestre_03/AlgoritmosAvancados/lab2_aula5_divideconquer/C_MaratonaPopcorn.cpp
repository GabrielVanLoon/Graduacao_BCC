#include <iostream>

using namespace std;

int n,c,t, min_guess, max_guess, chute, otimo;
int v[100000];

bool eh_suficiente(int tempo_max){

    int bag            = 0;
    int participantes  = c;
    int acumulado      = 0;
    int max_pipocas    = tempo_max * t;

    while(participantes > 0 && bag < n){

        // Se um bag sozinho já passa o limair então é impossível ser solução
        if(v[bag] > max_pipocas)
            return false;

        // o competidor atual ainda pode comer o proximo bag
        if(acumulado + v[bag] <= max_pipocas){
            acumulado += v[bag];
            bag++;

        // senão muda para o próximo participante.
        } else {
            participantes--;
            acumulado = 0;
        }
    }

    return (bag == n); // se bag == n então o tempo máximo foi suficiente.
}

int main(void){

    // qtd de pacotes, qtd de competidores, tempo maximo
    scanf("%d %d %d", &n, &c, &t);

    min_guess = 1;
    max_guess = 0;

    for(int i = 0; i < n; i++){
        scanf("%d", &v[i]);
        max_guess +=  v[i]/t;
        max_guess += (v[i]%t) ? 1 : 0;
    }

    otimo = max_guess;

    while(min_guess <= max_guess){
        
        chute = (min_guess + max_guess)/2;
        // printf("min: %d\tmax: %d\tchute: %d\n", min_guess, max_guess, chute);

        if(eh_suficiente(chute)){
            // printf("Alcança\n");
            otimo = chute;
            max_guess = chute-1;
        } else {
            // printf("Não Alcança\n");
            min_guess = chute+1;
        }
    }

    cout << otimo << endl;

}



