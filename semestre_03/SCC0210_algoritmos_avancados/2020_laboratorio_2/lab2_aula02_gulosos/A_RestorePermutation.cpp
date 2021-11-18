#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main(void){

    int casos = 0;
    scanf("%d", &casos);
    for(int k = 0; k < casos; k++){
        
        int         n, temp, count = 0;
        set<int>    memo;


        scanf("%d", &n);
        for(int i = 0; i < 2*n; i++){
            scanf("%d", &temp);
            // verificando se o número já apareceu
            if(memo.find(temp) == memo.end()){
                memo.insert(temp);
                count++;
                char c = (count == n) ? '\n': ' ';
                printf("%d%c",temp, c);
            }
        }

    }
    return 0;
}