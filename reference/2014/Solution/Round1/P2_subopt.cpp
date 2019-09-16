#include <stdio.h>
#include <algorithm>
using namespace std;

const int MAX_N = 1000000;

int N;
int A[MAX_N], B[MAX_N];
int S[MAX_N];

long long calcSol() {
	long long nA, nB, res;
	nA = nB = res = 0;
	for (int i=0;i<N;i++) {
		nA += A[i]; nB += B[i];
		res = max(nA, res);
		res = max(nB, res);

		if (S[i]) nB --;
		else nA --;

		if (nA < 0) nA = 0;
		if (nB < 0) nB = 0;
	}
	return res;
}

int main() {
	scanf("%d",&N);
	long long sol = 0;
	for (int i=0;i<N;i++){
		scanf("%d %d",&A[i],&B[i]);
		sol += max(A[i], B[i]);
	}

	for (long long i=0;i<(1ll <<N);i++) {
		for (int j=0;j<N;j++) {
			S[j] = !( i & (1ll <<j) );
		}
		sol = min(sol, calcSol());
	}

	printf("%lld\n", sol);
	return 0;
}