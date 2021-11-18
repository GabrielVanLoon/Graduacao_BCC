/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    Abril/2019
 * Aula 07  Busca Binária e Método da Bissecção
 */

/**
 * Exercicio 01 - Solucione a equação
 * UVA 10341
 */
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

int main(void){

    double p, q, r, s, t, u;

    while(cin >> p >> q >> r >> s >> t >> u){
        // Precisa verificar se a função cresce ou decresce
        double x, dx, eq, deq, min = 0.0, max = 1.0; 

        int it = 30;
        while(it--){

            x  = (min + max) / 2.0;
            dx = x + 0.0001;
            eq  = (p/exp(x)) + (q*sin(x)) + (r*cos(x)) + (s*tan(x)) + (t*x*x) + u;
            deq = (p/exp(dx)) + (q*sin(dx)) + (r*cos(dx)) + (s*tan(dx)) + (t*dx*dx) + u;

            // Se função crescente
            if(deq > eq){
                //cout << "Crescente...";
                if(eq > 0.0){
                    //cout << "diminui...";
                    max = x;
                } else {
                    //cout << "aumenta...";
                    min = x;
                }
            // Se função decrescente
            } else {
                //cout << "Decrescente...";
                if(eq > 0.0){
                    //cout << "aumenta...";
                    min = x;
                } else {
                    //cout << "diminui...";
                    max = x; 
                }
            }
        
            //printf("f(%.4lf) = %.4lf\t\t\tPrecisao: %.50lf\n", x, eq, precisao);
            // precisao = fabs(max-min);
        } 
        
        if(fabs(eq) < 0.0001){
            //printf("f(%.4lf) = %.4lf\t\t\tPrecisao: %.50lf\n", x, eq, precisao);
            printf("%.4lf\n", x);
        } else {
            printf("No solution\n");
        }

    }

    return 0;
}
