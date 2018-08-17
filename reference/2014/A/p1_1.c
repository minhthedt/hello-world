#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

//#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINT(...) printf(__VA_ARGS__)

#else
#define DEBUG_PRINT(...) do {} while (0)

#endif

struct word {
	int num;
	int pos;
};

int T;
int N;
int K;
int *threshold;
int threshold_sum;
int *tmp_threshold;
struct word *words;

static int find_solution()
{
	int i;
	int end;
	int min = INT_MAX;
	int tmp_sum = 0;
	int num, len;

	for (i = 0; i < K; i++) {
		tmp_threshold[i] = 0;
		tmp_sum += threshold[i];
	}

	end = 0;
	for (i = 0; i < N; i++) {
		while (tmp_sum != 0 && end < N) {
			num = words[end].num;
			if (tmp_threshold[num - 1] < threshold[num - 1])
				tmp_sum--;
			tmp_threshold[num - 1]++;
			end++;
		}

		if (tmp_sum != 0 && end >= N)
			break;

		len = words[end - 1].pos - words[i].pos + 1;
		if (len < min)
			min = len;

		num = words[i].num;
		if (tmp_threshold[num - 1] <= threshold[num - 1])
			tmp_sum++;
		tmp_threshold[num - 1]--;
	}

	if (min == INT_MAX)
		return -1;
	else
		return min;
}

static void run_test()
{
	int i;
	int err, ret;
	bool no_solution = false;

	err = scanf("%d %d\n", &N, &K);
	if (err != 2 || N < 1 || N > 1000000 || K < 1 || K > 1000) {
		fprintf(stderr, "Invalid Input\n");
		exit(1);
	}

	threshold = calloc(K, sizeof(int));
	tmp_threshold = calloc(K, sizeof(int));
	if (!threshold || !tmp_threshold) {
		fprintf(stderr, "No memory\n");
		exit(1);
	}

	for (i = 0; i < K; i++) {
		int num;

		err = scanf("%d\n", &num);
		if (err != 1 || num < 1) {
			fprintf(stderr, "Invalid Input\n");
			exit(1);
		}

		threshold[i] = num;
	}

	words = calloc(N, sizeof(struct word));
	if (!words) {
		fprintf(stderr, "No memory\n");
		exit(1);
	}

	for (i = 0; i < N; i++) {
		int x, y;
		struct word *w;

		err = scanf("%d %d\n", &x, &y);
		if (err != 2 || x < 1 || x > K || y < 1 || y > 5000000) {
			fprintf(stderr, "Invalid Input\n");
			exit(1);
		}

		w = &words[i];
		w->num = x;
		w->pos = y;
		tmp_threshold[x - 1]++;
	}

	for (i = 0; i < N; i++)
		DEBUG_PRINT("%d %d\n", words[i].num, words[i].pos);
	
	for (i = 0; i < K; i++)
		DEBUG_PRINT("%d\n", threshold[i]);
	
	for (i = 0; i < K; i++) {
		if (tmp_threshold[i] < threshold[i]) {
			no_solution = true;
			break;
		}
	}

	if (no_solution)
		ret = -1;
	else
		ret = find_solution();

	printf("%d\n", ret);


	free(threshold);
	free(tmp_threshold);
	free(words);
}

int main()
{
	int err;
	int i;

	err = scanf("%d\n", &T);
	if (err != 1 || T < 0 || T > 100) {
		fprintf(stderr, "Invalid Input\n");
		exit(1);
	}

	for (i = 0; i < T; i++)
		run_test();


	return 0;
}

