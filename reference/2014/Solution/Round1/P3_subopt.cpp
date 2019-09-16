#include <stdio.h>
#include <string.h>
#include <memory.h>

int n;
char str[1000][101];

int pi[101];

int ans[1000];
int ansidx[1000];

void input ()
{
	scanf ("%d", &n);

	for (int i=0; i<n; i++) {
		scanf ("%s", str[i]);
		for (int j=0; j<i; j++) {
			if (strcmp (str[i], str[j]) == 0) {
				while (true) {
				}
			}
		}
	}
}

int kmp (char* s, char* p)
{
	int ns = strlen(s);
	int np = strlen(p);

	pi[0] = -1;
	int j=-1;
	for (int i=1; i<np; i++) {
		while (j!=-1 && p[j+1] != p[i]) j = pi[j];
		if (p[j+1] == p[i]) j++;
		pi[i] = j;
	}

	int res = -1;
	j=-1;
	for (int i=0; i<ns; i++) {
		while (j!=-1 && p[j+1] != s[i]) j = pi[j];
		if (p[j+1] == s[i]) j++;

		if (res < j)
			res = j;
	}

	return res+1;
}

void find_answer ()
{
	memset (ans, 0, sizeof (int) * n);

	for (int i=0; i<n; i++) {
		for (int j=0; str[i][j]; j++) {
			int cnt = -1;
			for (int k=0; k<n; k++) if (i!=k) {
				int res = kmp (str[k], str[i] + j);
				if (cnt < res)
					cnt = res;
			}

			if (cnt < strlen(str[i]) - j && (ans[i]==0 || ans[i] > cnt+1)) {
				ans[i] = cnt+1;
				ansidx[i] = j;
			}
		}
	}
}

void output ()
{
	for (int i=0; i<n; i++)
		printf ("%d\n", ans[i]);
}

int main()
{
	input ();
	find_answer ();
	output ();

	return 0;
}
