/** 

414 Third Max Number

Given an integer array nums, return the third distinct maximum number in this array. If the third maximum does not exist, return the maximum number. 

Input: nums = [3,2,1]
Output: 1
Explanation:
The first distinct maximum is 3.
The second distinct maximum is 2.
The third distinct maximum is 1.

Url: https://leetcode.com/problems/third-maximum-number/

**/

int getThirdDistinctMax(const vector<int> v){
  
  // Ordenação
  std:sort(v.begin(), v.end(), std::greater<int>());
  
  int max = -1, i = 0, j = 0;

  for(i = 0; i < v.size() && j < 3; ){
    max = v[i++];
    j++;
    while(v[i] == v[i-1]) i++;
  }
  
  return max;
}

// Custo Tempo O(n logn) por causa da ordenação
// Custo Espaço O(1) pois não usa memória adicional além das variáveis

// Melhor solução: O(n) pois basta ler o vetor mantendo o tracking dos top 3 maiores valores.
//                 Faz sentido mas achei uma solução pouco genérica e extensível :P