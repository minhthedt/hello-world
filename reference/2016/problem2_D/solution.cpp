#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

#define NMAX 200003
#define TMAX 262144

int N, Q;

vector< pair<int, int> > edge[ NMAX ];

int before[ NMAX ];
int after[ NMAX ];

int degree[ NMAX ];
int timing[ NMAX ];
int height[ NMAX ];

int indextree[ TMAX * 2 + 3 ];

bool visit[ NMAX ];

void dfs(int now, int &count) {
    visit[now] = true;
    timing[now] = count;
    indextree[count + TMAX] = now;
    count ++;
    
    for (int i = 0; i < edge[now].size(); i ++) {
        if (visit[edge[now][i].first]) {
            continue;
        }
        height[edge[now][i].first] = height[now] + 1;
        before[edge[now][i].first] = before[now] + edge[now][i].second;
        dfs(edge[now][i].first, count);
        indextree[count + TMAX] = now;
        count ++;
    }
}

void LCA() {
    int cnt = 0;
    dfs(1, cnt);

    for (int i = TMAX - 1; i >= 1; i --) {
        if (height[indextree[i * 2]] < height[indextree[i * 2 + 1]]) {
            indextree[i] = indextree[i * 2];
        } else {
            indextree[i] = indextree[i * 2 + 1];
        }
    }

    memset( visit, 0, sizeof(visit) );
}

int dist(int a, int b) {
    int l = min(timing[a], timing[b]) + TMAX;
    int r = max(timing[a], timing[b]) + TMAX;
    int ret = indextree[l];

    while (l <= r) {
        if (l & 1) {
            if (height[ret] > height[indextree[l]]) {
                ret = indextree[l];
            }
            l ++;
        }
        if (!(r & 1)) {
            if (height[ret] > height[indextree[r]]) {
                ret = indextree[r];
            }
            r --;
        }
        l /= 2;
        r /= 2;
    }

    return before[a] + before[b] - before[ret] * 2;
}

void dijkstra() {
    priority_queue< pair<int, int> > Queue;

    Queue.push(make_pair(0, 1));
    while (!Queue.empty()) {
        int now = Queue.top().second;
        Queue.pop();

        if (visit[now]) {
            continue;
        }
        visit[now] = true;

        for (int i = 0; i < edge[now].size(); i ++) {
            int dest = edge[now][i].first;
            int weight = edge[now][i].second;

            if (after[dest] > after[now] + weight) {
                after[dest] = after[now] + weight;
                Queue.push(make_pair(-after[dest], dest));
            }
        }
    }
}

int main() {
    int T;
    scanf( "%d", &T );

    while (T --) {
        scanf( "%d %d", &N, &Q );

        for (int i = 2; i <= N; i ++) {
            int x, w;
            scanf( "%d %d", &x, &w );
            edge[i].push_back(make_pair(x, w));
            edge[x].push_back(make_pair(i, w));

            degree[x] ++;
            after[i] = 2147483647;
        }
        
        LCA();
        
        for (int i = 2; i <= N; i ++) {
            if (degree[i] == 0) {
                int w;
                scanf( "%d", &w );
                edge[i].push_back(make_pair(1, w));
                edge[1].push_back(make_pair(i, w));
            }
        }

        dijkstra();

        long long answer_first = 0;
        long long answer_second = 0;

        for (int i = 0; i < Q; i ++) {
            int a, b;
            scanf( "%d %d", &a, &b );
            int x = dist(a, b);
            answer_first += x;
            answer_second += min(x, after[a] + after[b]);
        }
        printf( "%lld %lld\n", answer_first, answer_second );

        for (int i = 1; i <= N; i ++) {
            edge[i].clear();

            before[i] = after[i] = 0;
            degree[i] = timing[i] = height[i] = 0;
            visit[i] = false;
        }
        for (int i = 0; i < TMAX + TMAX; i ++) {
            indextree[i] = 0;
        }
    }
    return 0;
}
