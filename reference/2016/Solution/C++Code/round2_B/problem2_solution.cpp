#include <stdio.h>

int N;
int start_w;
int A_w[5005], A_len[5005];
int B_w[5005], B_len[5005];
int point;
int M;

int now_w, total_w;
int answer;

void go(int w, int len) {
	total_w += len * now_w;
	if (w < now_w) now_w = w;
}

int main() {
	freopen("eval_input1.txt", "r", stdin);
	freopen("eval_output1.txt", "w", stdout);

	int i, j;
	int T; scanf("%d", &T); while (T--) {
		scanf("%d", &N); N--;
		scanf("%d", &start_w);
		for (i = 0; i < N; i++) scanf("%d%d", &A_len[i], &A_w[i]);
		scanf("%d%d", &point, &M); point--;
		for (i = 0; i < M; i++) scanf("%d%d", &B_len[i], &B_w[i]);

		answer = -1;

		for (i = 0; i <= M; i++) {
			now_w = start_w;
			total_w = 0;
			for (j = 0; j < point; j++) go(A_w[j], A_len[j]);
			for (j = 0; j < i; j++) go(B_w[j], B_len[j]);
			for (j = i - 1; j >= 0; j--) go(B_w[j], B_len[j]);
			for (j = point; j < N; j++) go(A_w[j], A_len[j]);

			if (answer<0 || answer>total_w) answer = total_w;
		}
		printf("%d\n", answer);
	}

}