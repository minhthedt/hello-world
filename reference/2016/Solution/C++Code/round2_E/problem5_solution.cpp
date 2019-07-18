#include <stdio.h>
#include <vector>
#include <algorithm>
#include <limits>
#include <memory.h>
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
int n, m, L, c[NM];
struct Coord {
	int x, y;
	inline int Abs(int x) {
		return (x>=0) ? x : -x;
	}
	int dist(Coord B) {
		return Abs(x - B.x) + Abs(y - B.y);
	}
}a[NM], b[NM];

void input() {
	si(n), si(m);
	FOR(i, 1, n) si(a[i].x), si(a[i].y);
	FOR(i, 1, m) si(b[i].x), si(b[i].y);
	FOR(i, 1, m) si(c[i]);
	si(L);
}
using namespace std;


// Reference : github.com/kcm1700
// usage:
// MaxFlowDinic::Init(n);
// MaxFlowDinic::AddEdge(0, 1, 100, 100); // for bidirectional edge
// MaxFlowDinic::AddEdge(1, 2, 100); // directional edge
// result = MaxFlowDinic::Solve(0, 2); // source -> sink
// graph[i][edgeIndex].res -> residual
//
// in order to find out the minimum cut, use `l'.
// if l[i] == 0, i is unrechable.

struct MaxFlowDinic
{
	typedef long long flow_t;

	struct Edge
	{
		int next;
		int inv; /* inverse edge index */
		flow_t res; /* residual */
	};

	int n;
	vector<vector<Edge>> graph;

	vector<unsigned> q, l, start;

	void Init(int _n) {
		n = _n;
		graph.resize(n);
		for (int i = 0; i < n; i++) graph[i].clear();
	}
	void AddNodes(int count) {
		n += count;
		graph.resize(n);
	}
	void AddEdge(int s, int e, flow_t cap, flow_t caprev = 0) {
		Edge forward = { e, graph[e].size(), cap };
		Edge reverse = { s, graph[s].size(), caprev };
		graph[s].push_back(forward);
		graph[e].push_back(reverse);
	}

	bool AssignLevel(int source, int sink) {
		int t = 0;
		memset(&l[0], 0, sizeof(l[0]) * l.size());
		l[source] = 1;
		q[t++] = source;
		for (int h = 0; h < t && !l[sink]; h++) {
			int cur = q[h];
			for (unsigned i = 0; i < graph[cur].size(); i++) {
				int next = graph[cur][i].next;
				if (l[next]) continue;
				if (graph[cur][i].res > 0) {
					l[next] = l[cur] + 1;
					q[t++] = next;
				}
			}
		}
		return l[sink] != 0;
	}

	flow_t BlockFlow(int cur, int sink, flow_t currentFlow) {
		if (cur == sink) return currentFlow;
		for (unsigned &i = start[cur]; i < graph[cur].size(); i++) {
			int next = graph[cur][i].next;
			if (graph[cur][i].res == 0 || l[next] != l[cur] + 1)
				continue;
			if (flow_t res = BlockFlow(next, sink, min(graph[cur][i].res, currentFlow))) {
				int inv = graph[cur][i].inv;
				graph[cur][i].res -= res;
				graph[next][inv].res += res;
				return res;
			}
		}
		return 0;
	}

	flow_t Solve(int source, int sink)
	{
		q.resize(n);
		l.resize(n);
		start.resize(n);
		flow_t ans = 0;
		while (AssignLevel(source, sink)) {
			memset(&start[0], 0, sizeof(start[0])*n);
			while (flow_t flow = BlockFlow(source, sink, numeric_limits<flow_t>::max())) {
				ans += flow;
			}
		}
		return ans;
	}
};

int pro(int L) {
	MaxFlowDinic mf;
	mf.Init(n + m + 2);
	FOR(i, 1, n) {
		mf.AddEdge(0, i, 1);
	}
	FOR(i, 1, m) {
		mf.AddEdge(n + i, n + m + 1, c[i]);
	}
	FOR(i, 1, n) {
		FOR(j, 1, m) {
			if (a[i].dist(b[j]) <= L) {
				mf.AddEdge(i, j + n, 1);
			}
		}
	}
	int flow = mf.Solve(0, n + m + 1);
	if (flow == n) return 1;
	return 0;
}

int main()
{
	int TT; si(TT);
	FOR(tt, 1, TT) {
		//fprintf(out, "Case #%d\n", tt);
		input();
		fprintf(out, "%d\n", pro(L));
		/*int max = 0;
		FOR(i, 1, n)FOR(j, 1, m) {
			if (max<a[i].dist(b[j]))
				max = a[i].dist(b[j]);
		}
		printf("%d\n", max);
		int left = 0, right = 200000000, mid, ans = INF;
		while (left <= right) {
			mid = (left + right) >> 1;
			int res = pro(mid);
			if (res == 1) ans = ans > mid ? mid : ans, right = mid - 1;
			else left = mid + 1;
		}
		fprintf(out, "%d\n", ans);*/
	}
	return 0;
}