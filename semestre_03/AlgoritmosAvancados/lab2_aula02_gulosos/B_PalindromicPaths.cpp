#include <iostream>

using namespace std;

int main(void){

    int casos = 0;
    scanf("%d", &casos);
    for(int k = 0; k < casos; k++){

        int n, m;
        scanf("%d %d", &n, &m);

        int max = (n > m) ? n : m;
        int matrix[n][m];

        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                scanf("%d", &(matrix[i][j]));
            }
        }

        // Qtd Diagonais == (n + m - 1)
        int qtd_diagonais = n + m - 1;
        int qtd_steps = qtd_diagonais/2;
        int total_swaps = 0;

        for(int s = 0; s < qtd_steps; s++){
            int i, j;
            
            int sup_ones = 0, sup_zeros = 0;
            int inf_ones = 0, inf_zeros = 0;

            // Matriz quadrada ou horizontal
            if(m >= n){
                i = 0, j = s;
                while(i < n && j >= 0){
                    (matrix[i][j] == 1) ? sup_ones++ : sup_zeros++;
                    i = i+1;
                    j = j-1;
                }

                i = n-1, j = (m-1-s);
                while(i >= 0 && j < m){
                    (matrix[i][j] == 1) ? inf_ones++ : inf_zeros++;
                    i = i-1;
                    j = j+1;
                }

            // Matriz Vertical
            } else {
                i = s, j = 0;
                while(i >= 0 && j < m){
                    (matrix[i][j] == 1) ? sup_ones++ : sup_zeros++;
                    i = i-1;
                    j = j+1;
                }

                i = n-1-s, j = (m-1);
                while(i < n && j >= 0){
                    (matrix[i][j] == 1) ? inf_ones++ : inf_zeros++;
                    i = i+1;
                    j = j-1;
                }            
            }

            int all_ones = sup_zeros + inf_zeros;
            int all_zeros = sup_ones + inf_ones;
            total_swaps += (all_ones < all_zeros) ? all_ones : all_zeros;
        }

        printf("%d\n", total_swaps);

    } // Fim Teste case

    return 0;
}