// Link: https://www.hackerrank.com/challenges/queue-using-two-stacks/problem

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

class EmulatedQueue {
    public:
        stack<int> q, buffer;
    
        void push(int e){ 
            buffer.push(e);
        }
        
        int front(){
            _flushBuffer();
            return q.top();
        }
        
        void pop(){
            _flushBuffer();
            q.pop();
        }
        
        void _flushBuffer(){
            if(q.empty()){
                while(!buffer.empty()){
                    q.push(buffer.top());
                    buffer.pop();
                }
            }
        }
};


int main() {
    
    EmulatedQueue emq;
    int n, opcode, aux;
     
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> opcode;
        
        switch(opcode){ 
            case 1: 
                cin >> aux;
                emq.push(aux);
                break;
            case 2: 
                emq.pop();
                break;
            case 3:
            default: 
                cout << emq.front() << endl;
        }
    }
    
    return 0;
}
