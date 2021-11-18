#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

int main(){

    string a;

    cin >> a;

    int count = 0;

    for(int i = 0, j = a.length() - 1; i < j; i++, j--) count += a[i] != a[j];

    cout << count << endl; 


    return 0;
}