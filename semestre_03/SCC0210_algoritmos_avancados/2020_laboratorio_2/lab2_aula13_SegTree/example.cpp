#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;

typedef vector<int> vi;

class SegTree {
private:
	vi st, A;
	int n;

	void build (int p, int L, int R){
		if (L == R){        // o intervalo é unitario
			st[p] = L;
		} else {
			build (2*p, L, (L+R)/2);
			build (2*p+1, (L+R)/2+1, R);

			int p1 = st[2*p], p2 = st[2*p+1];

			st[p] = (A[p1] <= A[p2]) ? p1 : p2;
		}

	}

	int rmq(int p, int L, int R, int i, int j){
		if (i > R || j < L )  return -1;     // a query esta FORA da faixa....
		if (L <= i && R <= j) return st[p];  // a quesru está dentro, retorna o valor..

		// verifica qual o valor maximo entre p1 e p2, nas partes esquerda e direta do intervalo
		int p1 = rmq(2*p, L, (L+R)/2, i,j);
		int p2 = rmq(2*p+1, (L+R)/2+1, R, i,j);

		if (p1 == -1) return p2;
		if (p2 == -1) return p1;

		return (A[p1] <= A[p2]) ? p1 : p2;

	}
		

public:

	int rmq (int i, int j){
		return rmq(1, 0, n-1, i, j);
	}

	SegTree(const vi & _A){
		A = _A;
		n = A.size();
		st.assign(n*4, 0);
		build(1, 0, n-1);
	}

};



int main(int argc, char const *argv[])
{
	int arr[] = {18,17,13,19,15,11,20};

	vi A(arr, arr+7);

	SegTree st(A);

	printf("RMQ(1,3) =  %d\n", st.rmq(1,3));
	printf("RMQ(4,6) =  %d\n", st.rmq(4,6));

}