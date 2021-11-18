#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CHAR 'A'

int  l, c, n;
char tab[40][40];
char words[20][41];
int  words_len[20];

int  count[40][40];
int  mask[20];

bool test_horiz(int w, int len, int x, int y){
    if(words_len[w] == len)
        return true;
    if(x >= l || y >= c)
        return false;
    
    for(int i = 0; i < words_len[w]; i++){
        // Verifica na w-esima palavra se possui o char
        if(words[w][i] == tab[x][y]){
            char backup = words[w][i];
            words[w][i] = '*';
            
            // marca o tile como parte do anagrama da w-esima palabra
            bool r = test_horiz(w,len+1,x,y+1);
            if(r == true){
                count[x][y] = count[x][y] | mask[w];
            }

            words[w][i] = backup;
            return r;
        }        
    }

    return false;
}

bool test_diag1(int w, int len, int x, int y){
    if(words_len[w] == len)
        return true;
    if(x >= l || y >= c)
        return false;
    
    for(int i = 0; i < words_len[w]; i++){
        // Verifica na w-esima palavra se possui o char
        if(words[w][i] == tab[x][y]){
            char backup = words[w][i];
            words[w][i] = '*';
            
            // marca o tile como parte do anagrama da w-esima palabra
            bool r = test_diag1(w,len+1,x+1,y+1);
            if(r == true){
                count[x][y] = count[x][y] | mask[w];
            }

            words[w][i] = backup;
            return r;
        }        
    }

    return false;
}

bool test_diag2(int w, int len, int x, int y){
    if(words_len[w] == len)
        return true;
    if(x < 0 || y < 0 || x >= l || y >= c)
        return false;
    
    for(int i = 0; i < words_len[w]; i++){
        // Verifica na w-esima palavra se possui o char
        if(words[w][i] == tab[x][y]){
            char backup = words[w][i];
            words[w][i] = '*';
            
            // marca o tile como parte do anagrama da w-esima palabra
            bool r = test_diag2(w,len+1,x+1,y-1);
            if(r == true){
                count[x][y] = count[x][y] | mask[w];
            }

            words[w][i] = backup;
            return r;
        }        
    }

    return false;
}

bool test_vert(int w, int len, int x, int y){
    if(words_len[w] == len)
        return true;
    if(x >= l || y >= c)
        return false;
    
    for(int i = 0; i < words_len[w]; i++){
        // Verifica na w-esima palavra se possui o char
        if(words[w][i] == tab[x][y]){
            char backup = words[w][i];
            words[w][i] = '*';
            
            // marca o tile como parte do anagrama da w-esima palabra
            bool r = test_vert(w,len+1,x+1,y);
            if(r == true){
                count[x][y] = count[x][y] | mask[w];
            }

            words[w][i] = backup;
            return r;
        }        
    }

    return false;
}


int main(void){

    // forjando a mascara
    mask[0] = 1;
    for(int i = 1; i < 20; i++){
        mask[i] = 2 * mask[i-1];
    }

    // Lendo o tabuleiro
    scanf(" %d %d", &l, &c);
    for(int i = 0; i < l; i++)
        for(int j = 0; j < c; j++)
            scanf(" %c", &tab[i][j]);
    
    // Lendo a palavra
    scanf(" %d", &n);
    for(int i = 0; i < n; i++){
        scanf(" %s", words[i]);
        words_len[i] = strlen(words[i]);
    }

    // Contando os tile que pertencem à anagramas
    for(int w = 0; w < n; w++){ // 1600 * 20 * (3*20)
        for(int i = 0; i < l; i++){
            for(int j = 0; j < c; j++){
                test_horiz(w,0,i,j);
                test_diag1(w,0,i,j);
                test_diag2(w,0,i,j);
                test_vert(w,0,i,j);
            }
        }
    }

    int resposta = 0;
    for(int i = 0; i < l; i++){
        for(int j = 0; j < c; j++){
            
            // printf("[%d][%d] - %d\n", i, j, count[i][j]);

            int temp_count = 0;
            for(int w = 0; w < n; w++){
                if(count[i][j] & mask[w]){
                    temp_count += 1;
                }
            }

            if(temp_count >= 2){
                resposta += 1;
            }
        }
    }

    printf("%d\n", resposta);
    
    return 0;
}