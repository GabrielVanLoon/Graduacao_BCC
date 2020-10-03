#include <iostream>
#include <string.h>
#include <string>

using namespace std;

char   str_a[200001], str_b[200001];
size_t str_len;

bool str_equals(int ia, int ja, int ib, int jb){
    // Caso base: string de tamanho 1
    if(ia == ja)
        return str_a[ia] == str_b[ib];

    // Se a string for de tamanho impar a recursão não se aplica, pois a1 e a2 
    // tem que ser do mesmo tamanho segundo a regra de equivalencia.
    int len_temp = ja-ia+1;
    if(len_temp%2 != 0){
        for(int i = 0; (ia+i) <= ja; i++){
            if(str_a[ia+i] != str_b[ib+i]){
                return false;
            }
        }
        return true;
    }

    // Se a string for de tamanho par aplica a recursão.
    int ma = (ia + ja)/2;
    int mb = (ib + jb)/2;

    bool cond1 = str_equals(ia,ma,ib,mb) && str_equals(ma+1,ja,mb+1,jb);
    bool cond2 = cond1 || str_equals(ia,ma,mb+1,jb) && str_equals(ma+1,ja,ib,mb);
    
    return cond1 || cond2;
}


int main(void){

    scanf(" %s %s", str_a, str_b);
    str_len = strlen(str_a);

    if(str_equals(0,str_len-1,0,str_len-1))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    return 0;
}