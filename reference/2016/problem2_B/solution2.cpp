#include <stdio.h>
#include <stdlib.h>

#define N 100005
#define INF 1000000000

int n;

int a[N], b[N], b2[N];

int d_y[4] = { 0,1,0, -1 };
int d_x[4] = { 1,0,-1,0 };

struct coord
{
	int x, y;
}ac[N],bc[N], tmp[N];

int get_buho(int t)
{
	if (t > 0) return 1;
	else return -1;
}

void make_coordinate(int p[], struct coord c[], int di)
{
	int y = 0, x = 0;
	for (int i = 1; i <= n; i++) {
		c[i].y = y;
		c[i].x = x;

		y += abs(p[i]) * d_y[di];
		x += abs(p[i]) * d_x[di];

		if (get_buho(p[i]) > 0) di = (di + 3) % 4;
		else di = (di + 1) % 4;
	}

	int minx = INF;
	int miny = INF;

	int origin = 0;
	for (int i = 1; i <= n; i++) {
		if (miny > c[i].y || miny == c[i].y && minx > c[i].x) {
			miny = c[i].y;
			minx = c[i].x;
			origin = i;
		}
	}

	for (int i = 1; i <= n; i++) {
		c[i].y -= miny;
		c[i].x -= minx;
	}

	for (int i = origin; i <= n; i++) {
		tmp[i - origin + 1] = c[i];
	}

	for (int i = 1; i < origin; i++) tmp[n - origin + 1 + i] = c[i];
	for (int i = 1; i <= n; i++) c[i] = tmp[i];

}

bool same_check(struct coord c1[], struct coord c2[])
{
	for (int i = 1; i <= n; i++) {
		if (c1[i].x != c2[i].x || c1[i].y != c2[i].y) return false;
	}
	return true;
}

bool process()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) scanf("%d", &b[i]);

	make_coordinate(a, ac, 0);

	for (int di = 0; di < 4; di++) {
		make_coordinate(b, bc, di);
		if (same_check(ac, bc)) return true;
	}

	for (int i = 1; i <= n; i++) b2[i] = abs(b[n - i + 1]);
	for (int i = 1; i <= n; i++) b2[i] *= get_buho(b[((n - i + 1) + n - 2) % n + 1]) * -1;
	
	for (int di = 0; di < 4; di++) {
		make_coordinate(b2, bc, di);
		if (same_check(ac, bc)) return true;
	}

	return false;	
}

int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++) {
		printf("%d\n", process());
	}
	return 0;
}