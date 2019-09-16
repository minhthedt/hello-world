#include <stdio.h>
#include <algorithm>

using namespace std;

const int MAX_N = 1000000;

int N;
long long cmA[MAX_N], cmB[MAX_N];
long long dA[MAX_N], dB[MAX_N];

bool calcDpos(long long &M, int &i, int &Dpos, 
			  long long cmX[], long long cmY[], 
			  long long &fX, long long& fY, 
			  long long dX[], long long dY[]) {
	while (cmX[i] - fX > M) {
		if (Dpos >= i) return false;
		if (Dpos > 0) {
			dX[Dpos] = dX[Dpos - 1];
			dY[Dpos] = dY[Dpos - 1];
		}

		if (dX[Dpos] < cmX[Dpos]) {
			dX[Dpos] ++;
			fX ++;
		} else if (dY[Dpos] < cmY[Dpos]) {
			dY[Dpos] ++;
			fY ++;
		}

		Dpos ++;
	}
	return true;
}

bool Possible(long long M) {
	long long fA, fB;
	fA = fB = 0;
	for (int i=0;i<N;i++) dA[i] = dB[i] = 0;

	int Dpos = 0;
	for (int i=0;i<N;i++) {
		if (!calcDpos(M, i, Dpos, cmA, cmB, fA, fB, dA, dB) || 
			!calcDpos(M, i, Dpos, cmB, cmA, fB, fA, dB, dA)) return false;
	}

	return true;
}

char rawdata[4096];
int npos = 4096, lpos;
char getC() {
	if (npos >= lpos) {	
		memset(rawdata, 0, sizeof(rawdata));
		lpos = fread(rawdata, 1, 4096, stdin);
		npos = 0;
	}
	return rawdata[npos ++];
}
long long getInteger64() {
	char c;
	bool flg = false;
	long long res = 0;
	while(1) {
		c = getC();
		if ('0' <= c && c <= '9') {
			res = res * 10 + c - '0';
			flg = true;
		} else if (flg) {
			break;
		}
	}
	return res;
}
int getInteger() {
	return (int)getInteger64();
}
int main() {
	npos = 4096;
	lpos = 4096;
	N = getInteger();
	long long mxA, mxB;
	mxA = mxB = 0;
	dA[0] = dB[0] = 0;
	for (int i=0;i<N;i++) {
		cmA[i] = getInteger64();
		cmB[i] = getInteger64();
		if (i > 0) { // cumulative 
			cmA[i] += cmA[i-1];
			cmB[i] += cmB[i-1];

			dA[i] = dA[i-1];
			dB[i] = dB[i-1];
		}
		mxA = max(mxA, cmA[i] - dA[i]);
		mxB = max(mxB, cmB[i] - dB[i]);
		if (dA[i] < cmA[i]) dA[i] ++;
		if (dB[i] < cmB[i]) dB[i] ++;
	}
	long long s = max(mxA, mxB);
	long long e = max(cmA[N-1], cmB[N-1])-1;
		
	while (s<=e) {
		long long m = (s+e) / 2;
		if (Possible(m)) e = m-1;
		else s = m+1;
	}

	long long sol = e+1;

	printf("%lld\n", sol);
	return 0;
}