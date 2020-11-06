#include <iostream>
#include <string.h>
#include <stdlib.h>

char a[1001], b[1001];
int  a_len, b_len, memo[1001][1001];

int calc_lcs(int i, int j){

    if( i == a_len || j == b_len )
        return  0;

    if(memo[i][j] != -1)
        return memo[i][j];

    if(a[i] == b[j])
        memo[i][j] = 1 + calc_lcs(i+1, j+1);
    else {
        int avanca_a = calc_lcs(i+1, j);
        int avanca_b = calc_lcs(i, j+1);

        memo[i][j] = (avanca_a > memo[i][j]) ? avanca_a : memo[i][j];
        memo[i][j] = (avanca_b > memo[i][j]) ? avanca_b : memo[i][j];
    }
    
    return memo[i][j];
}


int main(void){

    while( scanf("%[^\n]%*c%[^\n]%*c", a, b) != EOF ){
        
        // Reinicia a memoria
        memset(memo, -1, sizeof(memo));

        a_len = strlen(a);
        b_len = strlen(b);

        printf("%d\n", calc_lcs(0,0));

        memset(a, '\0', sizeof(a));
        memset(b, '\0', sizeof(b));
    }

    return 0;
}

