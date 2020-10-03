#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;

struct item{
    int valor;
    int index;
};

struct compare_item { 
    bool operator()(item const& p1, item const& p2) { 
        return p1.valor < p2.valor; 
    } 
}; 


int  N, Q, preco, relev, pos;
char produtos[100001][11];
char current_query[60];
item temp;
// priority_queue<item, vector<item>, compare_item> minprice_pq, maxprice_pq, relev_pq;

vector<item> minprice_pq, maxprice_pq, relev_pq;



int main()
{
    scanf("%d %d", &N, &Q);
    
    // Cadastrando os produtos
    for(int i = 0; i < N; i++){
        scanf("%s %d %d", produtos[i], &preco, &relev);

        temp = { -preco, i }; maxprice_pq.push_back(temp);
        temp = { preco, i }; minprice_pq.push_back(temp);
        temp = { -relev, i }; relev_pq.push_back(temp);
    }

    // Ordenando (n log n)
    sort(maxprice_pq.begin(), maxprice_pq.end(), compare_item());
    sort(minprice_pq.begin(), minprice_pq.end(), compare_item());
    sort(relev_pq.begin(), relev_pq.end(), compare_item());

    // Testando : OK
    // for(int i = 0; i < N; i++){
    //     cout << maxprice_pq[i].valor << " " << maxprice_pq[i].index << endl;
    // }
    // cout << endl;
    //    for(int i = 0; i < N; i++){
    //     cout << minprice_pq[i].valor << " " << minprice_pq[i].index << endl;
    // }
    // cout << endl;
    //    for(int i = 0; i < N; i++){
    //     cout << relev_pq[i].valor << " " <<relev_pq[i].index << endl;
    // }
    // cout << endl;
    char ord = 'n'; // 'n' >> NONE, 'm' >> min, 'M' >> MAx, 'R' >> relev
    for(int q = 0; q < Q; q++){
        scanf(" %s", current_query);


        if(strcmp(current_query, "ordenar_menor_preco") == 0){
            ord = 'm';
        } else if(strcmp(current_query, "ordenar_maior_preco") == 0){
            ord = 'M';
        } else if(strcmp(current_query, "ordenar_relevancia") == 0){
            ord = 'R';
        } else {
            scanf( "%d", &pos);

            switch(ord){
                case 'n': printf("%s\n", produtos[ pos-1 ]); break;
                case 'm': printf("%s\n", produtos[ minprice_pq[pos-1].index ]); break;
                case 'M': printf("%s\n", produtos[ maxprice_pq[pos-1].index ]); break;
                case 'R': printf("%s\n", produtos[ relev_pq[pos-1].index ]); break;
            }
        }
    }

    return 0;
}