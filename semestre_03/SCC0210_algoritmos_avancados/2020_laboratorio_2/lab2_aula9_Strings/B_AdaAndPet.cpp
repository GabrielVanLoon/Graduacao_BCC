#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

int    cases;
string pat;
int    pattern[600000];
long long repeats, pattern_size, total_lenght;

int main(void){
    
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);

    cin >> cases;
    for(int k = 0; k < cases; k++){
        // Lendo A e B
        cin >> pat >> repeats;

        // KMP 1ª Etapa -> Definindo a matriz de pattern
        int i = 0, j = 1;

        pattern[0]   = 0;
        pattern_size = 1;

        while(j < pat.size()){
            if(pat[i] == pat[j]){
                i += 1;
                j += 1;
                pattern[pattern_size++] = i;

            } else if(i != 0){
                i = pattern[i-1];
            } else {
                j += 1;
                pattern[pattern_size++] = 0;
            }
        }
        
        total_lenght = pat.size() + (repeats-1) * (pat.size() - pattern[pattern_size-1]);
        cout << total_lenght << endl;
    }

    return 0;
}