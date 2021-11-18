#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

int cases;
string str, pat;
vector<int> pattern, indexes;



int main(void){

    cin >> cases;
    for(int k = 0; k < cases; k++){
        
        // Resetando as variaveis
        indexes.clear(); 
        pattern.clear();

        // Lendo A e B
        cin >> str >> pat;

        // KMP 1ª Etapa -> Definindo a matriz de pattern
        int i = 0, j = 1;
        pattern.push_back(0);

        while(j < pat.size()){
            if(pat[i] == pat[j]){
                i += 1;
                j += 1;
                pattern.push_back(i);

            } else if(i != 0){
                i = pattern[i-1];
            } else {
                j += 1;
                pattern.push_back(0);
            }
        }
        
        // KMP 2ª Etapa -> Buscando os patterns
        i = 0, j = 0;
        while(i < str.size()){

            if(str[i] == pat[j]){
                i += 1;
                j += 1;

                if(j == pat.size()){
                    indexes.push_back(i - pat.size() + 1);
                    j = pattern[j-1];
                }
            } else if(j != 0) {
                j = pattern[j-1];
            } else {
                i += 1;
            }
        }

        // Imprimindo o resultado
        if(k != 0) 
            cout << endl;
        if(indexes.size() == 0)
            cout << "Not Found" << endl;
        else{
            cout << indexes.size() << endl << indexes[0];
            for(i = 1; i < indexes.size(); i++)
                cout << " " << indexes[i];
            cout << endl;
        }
    }


    return 0;
}