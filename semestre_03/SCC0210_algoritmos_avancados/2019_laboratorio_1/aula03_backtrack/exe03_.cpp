/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    Mar/2018
 * Aula 03	Back Tracking I
 */

/** 
 * Exercicio 03
 */
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

int n, a, b, c;
int x, y, z;

int main(){
    
    // Qtd. de testes.
    cin >> n;

    for(int i = 0; i < n; i++){
        cin >> a >> b >> c;

        bool hasSolution = false;
        int  cSqrt = sqrt(c);

        for(x = -cSqrt; x <= cSqrt; x++ ){      // 10^2
            for(y = x; y <= cSqrt; y++){        // 10^2
                for(z = y; z <= cSqrt; z++){    // 10^2
                    // cout << "Testando" << x << " " << y << " " << z << endl; 
                    
                    int eq1 =  x + y + z;
                    int eq2 =  x * y * z;
                    int eq3 = (x*x) + (y*y) + (z*z);

                    if(eq1==a && eq2==b && eq3==c){
                        cout << x << " " << y << " " << z << endl; 
                        hasSolution = true;
                        break;
                    }

                }
                if(hasSolution) break;
            }
            if(hasSolution) break;
        }

        if(!hasSolution) 
            cout << "No solution." << endl;
    }

    return 0;
}