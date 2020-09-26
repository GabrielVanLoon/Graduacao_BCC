#include <iostream>
#include <set>
#include <string>

using namespace std;

struct str_compare {
    bool operator() (const string& lhs, const string& rhs) const {
        if(lhs.size() == rhs.size())
            return lhs.compare(rhs) < 0;
        return lhs.size() < rhs.size();
    }
};


int     kases, k, N;
char    m[20][20];
string  str;
char    visitado = 0;
set<string, str_compare> dicionario;

void busca(int i, int j, int strlen){ 
    char backup = m[i][j];
    m[i][j] = visitado;

    // Insere o caracter na string atual
    str.push_back(backup);
    // cout << str << endl;

    // Se for palavra valida adiciona no dicionario
    if(strlen >= 3) 
        dicionario.insert(str);
    
    // Olhando para os 4 vizinhos diretos
    if(i-1 >= 0 && m[i-1][j] > backup)
        busca(i-1, j, strlen+1);
    if(j-1 >= 0 && m[i][j-1] > backup)
        busca(i, j-1, strlen+1);
    if(i+1 < N && m[i+1][j] > backup)
        busca(i+1, j, strlen+1);
    if(j+1 < N && m[i][j+1] > backup)
        busca(i, j+1, strlen+1);

    // Olhando os 4 vizinhos diagonais
    if(i-1 >= 0 && j-1 >= 0 && m[i-1][j-1] > backup)
        busca(i-1, j-1, strlen+1);
    if(i-1 >= 0 && j+1 < N && m[i-1][j+1] > backup)
        busca(i-1, j+1, strlen+1);
    if(i+1 < N && j-1 >= 0 && m[i+1][j-1] > backup)
        busca(i+1, j-1, strlen+1);
    if(i+1 < N && j+1 < N && m[i+1][j+1] > backup)
        busca(i+1, j+1, strlen+1);

    // Remove o caracter da string atual
    str.pop_back();
    m[i][j] = backup;
}


int main(void){

    scanf("%d", &kases);
    for(k = 0; k < kases; k++){
        dicionario.clear();
        str.clear();

        // Preenchendo a matriz
        scanf("%d", &N);   
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                scanf(" %c", &m[i][j]);

        // Realizando as buscas por palavras
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                busca(i,j,1);

        // Caso não seja o primeiro caso
        if(k != 0) printf("\n");

        // Exibindo as palavras encontradas
        set<string>::iterator dic_it;
        for(dic_it = dicionario.begin(); dic_it != dicionario.end(); dic_it++)
            cout << *dic_it << endl;
    }


    return 0;
}