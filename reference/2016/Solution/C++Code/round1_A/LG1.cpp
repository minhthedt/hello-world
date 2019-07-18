#include <stdio.h>
#include <vector>

using namespace std;

vector<int> v[500002];

int max(int x, int y){return x>y?x:y;}

int dfs(int x){
	int depth = 0;

	for(int i : v[x])
		depth = max(depth, dfs(i));
	
	return depth + 1;
}

int main(){
	int N, root;
	int i;
	int x, y;

	int T; scanf("%d",&T); while(T--){
		scanf("%d",&N);
		root = (N * (N+1)) >> 1;
		for(i=1;i<=N;i++) v[i].clear();
		for(i=1;i<N;i++){
			scanf("%d%d",&x,&y);
			v[x].push_back(y);
			root -= y;
		}
		printf("%d\n",dfs(root));
	}
	return 0;
}