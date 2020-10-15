#include <iostream>
#include <string.h>
#include <map>
#include <stack>

using namespace std;

int n;
int             values[2*100005], prev_i[2*100005];
map<int, int>   memo, pos;
stack<int>      seq;


int main(void){
    // Reinicia a memoria
    memset(prev_i,-1, sizeof(prev_i));
    memo.clear();
    pos.clear();

    // Lendo as entradas
    long long max_sequence = -1;
    long long max_temp  = -1;
    int  last_element = -1;

    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &values[i]);
        max_temp    = 1+memo[values[i]-1];
        prev_i[i]   = pos[values[i]-1];

        if(max_temp > memo[values[i]]){
            memo[values[i]] = max_temp;
            pos[values[i]]  = i;
        }

        if(memo[values[i]] > max_sequence){
            max_sequence = memo[values[i]];
            last_element = i;
        }
    }
    
    while(last_element != 0){
        seq.push(last_element);
        last_element = prev_i[last_element];
    }


    cout << max_sequence << endl;
    while(!seq.empty()){
        cout << seq.top() << " ";
        seq.pop();
    }

}