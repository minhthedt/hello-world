#include <stdio.h>
#include <vector>
#include <algorithm>
#define FOR(i,n,m) for (int i=(n);i<=(m);i++)
#define si(n) fscanf(in,"%d",&n)
#define sl(n) fscanf(in,"%lld",&n)
#define sd(n) fscanf(in,"%lf",&n)
#define NM 1005
#define MOD 1000000007
#define INF 0x7fffffff
#define vi vector<int>
//FILE *in = fopen("input.txt", "r"), *out = fopen("output.txt", "w");
FILE *in = stdin, *out = stdout;

// Reference : github.com/rhs0266

#include <math.h>
using namespace std;
typedef int T;
#define vp vector<POINT>
#define EPS 0
struct POINT {
	T x, y, dis;
	double angle;
	POINT() {};
	POINT(T _x, T _y) :x(_x), y(_y) {};
	bool operator()(POINT A, POINT B) {
		return A.y < B.y;
	}
	bool operator<(const POINT &rhs) {
		if (-EPS < angle - rhs.angle && angle - rhs.angle < EPS) return dis < rhs.dis;
		return angle < rhs.angle;
	}
	double dist(const POINT &rhs) {
		return sqrt((x - rhs.x)*(x - rhs.x) + (y - rhs.y)*(y - rhs.y));
	}
};
struct ConvexHull {
private:
	vp a, output;
	int n;

	int ccw(POINT a, POINT b, POINT c) {
		T t = (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
		if (t > EPS) return 1;
		if (t < EPS) return -1;
		return 0;
	}

	void calc() {
		sort(a.begin(), a.end(), POINT());
		a[0].angle = -10000;
		for (int i = 1; i < n; i++) {
			a[i].angle = atan2(a[i].y - a[0].y, a[i].x - a[0].x);
			a[i].dis = (a[i].y - a[0].y)*(a[i].y - a[0].y) + (a[i].x - a[0].x)*(a[i].x - a[0].x);
		}
		sort(a.begin(), a.end());

		vp stack;
		stack.push_back(a[0]);
		if (n == 1) {
			output = stack;
			return;
		}
		stack.push_back(a[1]);
		for (int i = 2; i < n; i++) {
			while (stack.size() > 1) {
				int m = stack.size();
				int t = ccw(stack[m - 2], stack[m - 1], a[i]);
				if (t <= 0) stack.pop_back();
				else break;
			}
			stack.push_back(a[i]);
		}
		output = stack;
	}

public:
	ConvexHull() {};
	ConvexHull(vp _input) {
		a.clear(); output.clear();
		a = _input;
		n = a.size();
		calc();
	}
	void push(POINT p) {
		a.push_back(p);
		n = a.size();
	}
	vp Solve() {
		calc();
		return output;
	}
	vp result() {
		return output;
	}
};

int point[NM][2];
int n;
int ccw(int ax, int ay, int bx, int by, int cx, int cy) {
	T t = (bx - ax)*(cy - ay) - (by - ay)*(cx - ax);
	if (t > EPS) return 1;
	if (t < EPS) return -1;
	return 0;
}
void input(int Num) {
	si(n);
	if (n > 200) {
		puts("Error 1");
	}
	FOR(i, 1, n) {
		si(point[i][0]), si(point[i][1]);
		if (point[i][0] < 0 || point[i][0]>10000 || point[i][1] < 0 || point[i][1]>10000) {
			puts("Error 2");
		}
	}
	FOR(i, 1, n) FOR(j, i + 1, n) FOR(k, j + 1, n)
		// (i-j).y/(i-j).x == (i-k).y/(i-k).x
		if ((point[i][1] - point[j][1])*(point[i][0] - point[k][0]) == (point[i][1] - point[k][1])*(point[i][0] - point[j][0]))
			puts("Error 3");
		else if (ccw(point[i][0], point[i][1], point[j][0], point[j][1], point[k][0], point[k][1]) == 0)
			puts("Error 3");
	if (Num >= 46 && Num <= 90) {
		ConvexHull cv = ConvexHull();
		FOR(i, 1, n) cv.push(POINT(point[i][0], point[i][1]));
		vp res = cv.Solve();
		if (res.size() != n)
			puts("Error 4");
	}
}
void pro() {
	double ans = INF * 1000.0;
	FOR(i, 1, n) {
		FOR(j, 1, n) {
			if (i == j) continue;
			ConvexHull cv1 = ConvexHull(), cv2 = ConvexHull();
			FOR(k, 1, n) {
				if (k == min(i,j)) cv1.push(POINT(point[k][0], point[k][1]));
				else if (k == max(i,j)) cv2.push(POINT(point[k][0], point[k][1]));
				else {
					int t = ccw(point[i][0], point[i][1], point[j][0], point[j][1], point[k][0], point[k][1]);
					if (t == 1) cv1.push(POINT(point[k][0], point[k][1]));
					else cv2.push(POINT(point[k][0], point[k][1]));
				}
			}
			double length = 0.0;
			vp res1 = cv1.Solve(), res2 = cv2.Solve();
			res1.push_back(res1[0]); res2.push_back(res2[0]);
			for (int i = 0; i < res1.size() - 1; i++) {
				length += res1[i].dist(res1[i + 1]);
			}
			for (int i = 0; i < res2.size() - 1; i++) {
				length += res2[i].dist(res2[i + 1]);
			}
			//ans = ans < length ? ans : length;
			if (ans > length) {
				ans = length;
			}
		}
	}
	fprintf(out, "%.5lf\n", ans);
}
int main() {
	int TT; si(TT);
	FOR(tt, 1, TT) {
		input(tt);
		//fprintf(out, "Case #%d\n", tt);
		pro();
	}
	return 0;
}