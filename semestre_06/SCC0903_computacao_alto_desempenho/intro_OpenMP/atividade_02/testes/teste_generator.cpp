#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char** argv){

    srand(time(NULL));

    int row, col, min, max;

    cin >> row >> col >> min >> max;
    cout << row << " " << col << endl;

    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            cout << rand() % max + min << " ";
        }
        cout << endl;
    }

    return 0;
}