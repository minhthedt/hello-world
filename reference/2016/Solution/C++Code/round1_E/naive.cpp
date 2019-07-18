#include <stdio.h>

int N,P[2020],S[2020],D[2020][2020];

int main()
{
	freopen ("input.txt","r",stdin);
	freopen ("output.txt","w",stdout);

	int T; scanf ("%d",&T); while (T--){
		scanf ("%d",&N);
		for (int i=0;i<N;i++) scanf ("%d",&P[i]);
		int sum = 0;
		for (int i=0;i<N;i++) scanf ("%d",&S[i]), sum += S[i];
		fprintf (stderr,"%d %d\n",N,sum);

		int ans = 0;
		for (int i=0;i<N;i++) for (int j=0;j<N;j++) D[i][j] = 0;
		for (int l=1;l<N;l++){
			for (int i=0;i<N;i++){
				int j = (i + l) % N;
				if (S[i] + S[j] == 1){
					D[i][j] = P[i] * P[j];
					if (l >= 2) D[i][j] += D[(i+1)%N][(j+N-1)%N];
				}
				for (int k=i;k!=j;k=(k+1)%N){
					int a = D[i][k], b = D[(k+1)%N][j];
					if (D[i][j] < a + b)
						D[i][j] = a + b;
				}

				if (ans < D[i][j])
					ans = D[i][j];
			}
		}

		printf ("%d\n",ans);
	}
	return 0;
}