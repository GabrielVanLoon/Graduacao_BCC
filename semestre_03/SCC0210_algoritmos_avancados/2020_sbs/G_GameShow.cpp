#include <stdio.h>
#include <stdlib.h>

int C, temp, score, max_score;

int main(void){

    score = max_score = 100;
    scanf("%d", &C);

    for(int i = 0; i < C; i++){
        scanf("%d", &temp);
        score += temp;
        if(score > max_score)
            max_score = score;
    }
    printf("%d\n", max_score);

    return 0;
}