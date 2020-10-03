#include <cstdio>
#include <iostream>
#include <map>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

int main(){

    int n;
    cin >> n;

    map<string, priority_queue<int>> list_sell, list_buy;

    string product, action;
    int value, profit = 0;

    for(int i = 0; i < n; i++){

        cin >> action >> product >> value;

        if(action == "Compra"){
            list_buy[product].push(-1 * value);
        }

        else{
            list_sell[product].push(value);
        }

        if(!list_sell[product].empty() && !list_buy[product].empty() && (-1*list_buy[product].top()) < list_sell[product].top()){
            profit += list_sell[product].top() - ((-1)*list_buy[product].top());
            list_sell[product].pop();
            list_buy[product].pop();
        }
        
    }

    cout << profit << endl;

    return 0;
}