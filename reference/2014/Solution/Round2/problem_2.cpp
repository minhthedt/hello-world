#include <stdio.h>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

#define MAXN 100005
#define MAXE 600005
typedef long long lld;

int T,N,M,K,E; lld ans,sec;
int P[MAXN],H[MAXN],mom[MAXN][17],maxe[MAXN][17];
vector <int> con[MAXN],conv[MAXN];
queue <int> que;

struct EDGE{
	int s,e,w;
	bool chk;
	bool operator < (const EDGE &ot)const{
		return w<ot.w;
	}
} edge[MAXE];

int find(int n){ return n==P[n]?n:(P[n]=find(P[n])); }

void bfs()
{
	int i,j,k,q;
	for (i=1;i<=N;i++) for (j=0;j<17;j++) maxe[i][j] = -1e9, mom[i][j] = 0;
	mom[1][0] = 1;
	que.push(1);
	while (!que.empty()){
		q = que.front(); que.pop();
		for (i=con[q].size();i--;){
			k = con[q][i];
			if (!mom[k][0])
				mom[k][0] = q, maxe[k][0] = conv[q][i], H[k] = H[q]+1, que.push(k);
		}
	}
	for (i=1;i<17;i++) for (j=1;j<=N;j++) mom[j][i] = mom[mom[j][i-1]][i-1], maxe[j][i] = max(maxe[j][i-1],maxe[mom[j][i-1]][i-1]);
}

int get_max_edge(int a,int b)
{
	if (H[a] < H[b]) swap(a,b);
	int i,k,ret=-1e9;
	for (i=0,k=H[a]-H[b];k;i++,k>>=1) if (k&1) ret = max(ret,maxe[a][i]), a = mom[a][i];
	if (a == b) return ret;
	for (i=17;i--;) if (mom[a][i] != mom[b][i]){
		ret = max(ret,maxe[a][i]);
		ret = max(ret,maxe[b][i]);
		a = mom[a][i], b = mom[b][i];
	}
	ret = max(ret,maxe[a][0]);
	ret = max(ret,maxe[b][0]);
	return ret;
}

int main()
{
	int i,a,b,c;
	for (scanf("%d",&T);T--;){
		scanf("%d%d%d",&N,&M,&K);
		ans = 0;
		for (i=1;i<=M;i++){
			scanf("%d%d%d",&a,&b,&c);
			edge[i].s = a; edge[i].e = b; edge[i].w = -c;
			ans += c;
		}
		for (i=1;i<=K;i++){
			scanf("%d%d%d",&a,&b,&c);
			edge[M+i].s = a; edge[M+i].e = b; edge[M+i].w = c;
		}
		E = M+K;
		sort(edge+1,edge+E+1);
		for (i=1;i<=N;i++) P[i] = i, con[i].clear(), conv[i].clear();
		for (i=1;i<=E;i++){
			edge[i].chk = 0;
			a = find(edge[i].s), b = find(edge[i].e);
			if (a == b) continue;
			con[edge[i].s].push_back(edge[i].e); conv[edge[i].s].push_back(edge[i].w);
			con[edge[i].e].push_back(edge[i].s); conv[edge[i].e].push_back(edge[i].w);
			P[b] = a;
			ans += edge[i].w;
			edge[i].chk = 1;
		}
		bfs();
		sec = 1e16;
		for (i=1;i<=E;i++) if (!edge[i].chk){
			sec = min(sec,ans+edge[i].w-get_max_edge(edge[i].s,edge[i].e));
		}
		printf("%lld %d\n",ans,ans!=sec);
	}
}