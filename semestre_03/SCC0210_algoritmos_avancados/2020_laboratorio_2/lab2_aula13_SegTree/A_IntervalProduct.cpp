#include <iostream>
#include <stdlib.h>

#define MAX_N 100001

using namespace std;

int N, K, v[MAX_N], arg1, arg2;
int ST[4*MAX_N], result; 
char query;

int init_segtree(int i, int l, int r){

    // Chegou na folha
    if(l == r) {
        ST[i] = v[l];
    
    // Inicia No não-folha
    } else {
        int  m = (l+r)/2;
        int child_l = init_segtree(2*i, l,  m);
        int child_r = init_segtree(2*i+1, m+1,r);

        ST[i] = child_l * child_r;
    }
     
    return ST[i];
}

int get_product(int i, int l, int r, int start, int end){

    // Segmento dentro do de interesse
    if(start <= l && r <= end)
        return ST[i];
    
    // Segmento fora do interesse -> retorna valor neutro
    if(end < l || r < start)
        return 1;

    // Expande o produto para os filhos.
    int  m = (l+r)/2;
    int child_l = get_product(2*i, l,  m, start, end);
    int child_r = get_product(2*i+1, m+1,r, start, end);

    return child_l * child_r;
}

int update_tree(int i, int l, int r, int indice, int value){

    // Indice não afeta o segmento atual
    if(indice > r || indice < l)
        return ST[i];

    // Chegou na folha do indice desejado
    else if(r == l && r == indice){
        ST[i] = value;

    // Indice afeta o segmento atual
    } else {
        int  m = (l+r)/2;
        int child_l = update_tree(2*i, l,  m, indice, value);
        int child_r = update_tree(2*i+1, m+1,r, indice, value);
        ST[i] = child_l * child_r;
    } 

    return ST[i];
}


int main(void){

    while(scanf(" %d %d", &N, &K) != EOF){

        // Lendo as entradas e normalizando para [-1,0,1]
        for(int i = 1; i <= N; i++){
            scanf("%d", &v[i]);
            //printf("%d -> ", v[i]);
            if(v[i] != 0){
                v[i] /= (v[i] < 0) ? -v[i] : v[i];
            }
            //printf("%d\n", v[i]);
        } 

        // Gerando a SegTree
        init_segtree(1, 1, N);

        // Lendo as queryes
        for(int i = 1; i <= K; i++){
            scanf(" %c %d %d", &query, &arg1, &arg2);

            // C indice valor
            // P inicio fim
            if(query == 'P'){
                result = get_product(1,1,N,arg1,arg2);

                if(result == 0)         printf("0");
                else if(result == 1)    printf("+");
                else                    printf("-");

            } else {
                // printf("\n%d -> ", arg2);
                if(arg2 != 0){
                    arg2 /= (arg2 < 0) ? -arg2 : arg2;
                }
                // printf("%d\n", arg2);
                update_tree(1,1,N,arg1,arg2);
            }
        }
        printf("\n");
    }

    return 0;
}
