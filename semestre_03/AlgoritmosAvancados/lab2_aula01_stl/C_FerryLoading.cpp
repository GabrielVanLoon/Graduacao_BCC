#include <iostream>
#include <queue>

using namespace std;

int main(void){

    int casos;
    scanf("%d", &casos);

    for(int c = 0; c < casos; c++){
        int     l, m, temp, crosses = 0;
        char    str[15], cur = 'l'; 
        queue<int> left, right;
        
        scanf(" %d %d", &l, &m);
        l = l * 100;

        for(int i = 0; i < m; i++){
            scanf(" %d %s", &temp, str);
            if(str[0] == 'l'){
                left.push(temp);
            } else {
                right.push(temp);
            }
        }

        while(!right.empty() || !left.empty()){
            crosses += 1;
            int espaco = l;
            
            if(cur == 'l'){
                while(!left.empty() && espaco - left.front() >= 0){
                    espaco = espaco - left.front();
                    left.pop();
                }
                cur = 'r';
            }
            
            else if(cur == 'r'){
                while(!right.empty() && espaco - right.front() >= 0){
                    espaco = espaco - right.front();
                    right.pop();
                }
                cur = 'l';
            }
        }
        
        printf("%d\n", crosses);

    }

    return 0;
}