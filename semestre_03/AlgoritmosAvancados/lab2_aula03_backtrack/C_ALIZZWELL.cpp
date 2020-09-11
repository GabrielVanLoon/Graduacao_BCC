#include <iostream>
using namespace std;

int  kases,r,c;
char m[100][100];
char str[] = "ALLIZZWELL"; // len: 10 

bool possui_caminho(int next, int i, int j){
    // condicao de parada: achou toda a string
    if(next == 10){
        return true;
    }

    // Para nao repetir, muda temporariamente o tile atual
    char temp = m[i][j];
    m[i][j] = '.';

    // printf("%d %d %d\n",i, j, next);

    // Olhando todos os arredores
    int left  = j-1;
    int right = j+1;
    int top   = i-1;
    int bot   = i+1;

    bool achou = false;

    // laterais
    if(left >= 0 && m[i][left] == str[next])
        achou = achou || possui_caminho(next+1,i,left);
    if(!achou && right < c && m[i][right] == str[next])
        achou = achou || possui_caminho(next+1,i,right);
    if(!achou && top >= 0 && m[top][j] == str[next])
        achou = achou || possui_caminho(next+1,top,j);
    if(!achou && bot < r && m[bot][j] == str[next])
        achou = achou || possui_caminho(next+1,bot,j);

    // quinas  
    if(!achou && top >= 0 && left >= 0 && m[top][left] == str[next])
        achou = achou || possui_caminho(next+1,top,left);
    if(!achou && top >= 0 && right < c && m[top][right] == str[next])
        achou = achou || possui_caminho(next+1,top,right);
    if(!achou && bot <  r && left >= 0 && m[bot][left] == str[next])
        achou = achou || possui_caminho(next+1,bot,left);
    if(!achou && bot <  r && right < c &&  m[bot][right] == str[next])
        achou = achou || possui_caminho(next+1,bot,right);
    
    // restaura o tile ao normal
    m[i][j] = temp;

    return achou;
}


int main(void){

    scanf("%d",&kases);
    for(int k = 0; k < kases; k++){
        
        // Lendo os valores da matriz
        scanf("%d %d", &r, &c);
        for(int i = 0; i < r; i++){
            for(int j = 0; j < c; j++){
                scanf(" %c",&m[i][j]);
            }
        }

        bool achou = false;
        //Verificando o path
        for(int i = 0; i < r; i++){
            if(achou) break;
            for(int j = 0; j < c; j++){
                if(achou) break;
                if(m[i][j] == 'A')
                    achou = achou || possui_caminho(1,i,j);
            }
        }

        if(achou)   printf("YES\n");
        else        printf("NO\n");
           
    }

    return 0;
}