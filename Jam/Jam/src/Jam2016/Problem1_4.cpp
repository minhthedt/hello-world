#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
#include <chrono>
#include <math.h>
#include <utility>      // std::pair, std::make_pair
#include <unordered_map>
#include <queue>
using namespace std;

namespace Jam2016
{
#define UINT8 unsigned char
#define INT16 short int
#define UINT32 unsigned int
#define INT32  int
#define INT64 signed long long
#define UINT64 unsigned long long
#define PI  3.1415926535897932384626344
    //tư tưởng bài toán ko đặc biệt, nhưng cách xử lý tính toán rất tối ưu
    void dijkstra_shortest_path(unordered_map<int, unordered_map<int, int>>& edges, vector<int>& length, int src)   // dijkstra shortest path (one to all)
    {
        length[src] = 0;
        priority_queue <pair<int, int>> pq;
        pq.push(make_pair(0, src));
        while (!pq.empty()) {
            //int cost = -pq.top().first;//?????????? không hiểu vì sao lời giải lại thêm dấu -
            int cost = pq.top().first;
            int here = pq.top().second;
            pq.pop();
            if (length[here] < cost) continue;
            for (auto i : edges[here]) {
                int there = i.first;
                int nextDist = cost + i.second;
                if (length[there] > nextDist) {
                    length[there] = nextDist;
                    //pq.push(make_pair(-nextDist, there));//???????? không hiểu vì sao lời giải lại thêm dấu -
                    pq.push(make_pair(nextDist, there));
                }
            }
        }
    }

    void make_lca(unordered_map<int, unordered_map<int, int>>& tree, int n, vector<int>& lca_tree, vector<int>& dist, vector<int>& height, int src)
    {
        queue<int> q;
        q.push(src);
        lca_tree[src] = 1, dist[src] = 0, height[src] = 1;
        //BFS
        while (q.size() > 0) {
            int current = q.front();
            q.pop();
            for (auto i : tree[current]) {
                if (lca_tree[i.first] == 0) {
                    lca_tree[i.first] = current;//parent của i.first là current
                    dist[i.first] = dist[current] + i.second;//khoảng cách từ i.first tới src
                    height[i.first] = height[current] + 1;//chiều cao của node i.first
                    q.push(i.first);
                }
            }
        }
    }

    //khá hay khi tìm Least Common Ancestor 
    int get_shortest_path(vector<int>& lca_tree, vector<int>& dist, vector<int>& h, int src, int end)
    {
        int s1 = src, s2 = end;
        if (h[s1] > h[s2]) swap(s1, s2);
        while (h[s1] != h[s2]) s2 = lca_tree[s2];
        while (s1 != s2)       s1 = lca_tree[s1], s2 = lca_tree[s2];  // s1(s1) = LCA
        return dist[src] + dist[end] - 2 * dist[s1];
    }

    void Run_Problem1_4(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);
        if (fi)
        {
            int testcase, n, q, a, b, m;


            cin >> testcase;
            printf("%d\n", testcase);
            while (testcase--)
            {
                cin >> n >> q;
                // make tree
                unordered_map<int, unordered_map<int, int>> tree;
                for (int i = 2; i <= n; i++) {
                    cin >> a >> b;
                    tree[i][a] = tree[a][i] = b;
                }

                // make graph (added node)
                unordered_map<int, unordered_map<int, int>> graph(tree);
                for (int i = 2; i <= n; i++) {
                    if (graph[i].size() == 1) {
                        cin >> m;
                        if (graph[i].find(1) == graph[i].end() || graph[i][1] > m)
                            graph[i][1] = graph[1][i] = m;
                    }
                }

                // make lca tree & get_shortest_path
                vector<int> lca_tree(n + 1, 0), dist(n + 1, 0), height(n + 1, 0);
                make_lca(tree, n, lca_tree, dist, height, 1);
                // get shortest length from root
                vector<int> short_len(n + 1, 10000000);
                dijkstra_shortest_path(graph, short_len, 1);
                long long fst = 0, snd = 0;
                for (int i = 0; i < q; i++) {
                    cin >> a >> b;
                    int prev = get_shortest_path(lca_tree, dist, height, a, b);
                    int next = min(prev, short_len[a] + short_len[b]);
                    fst += prev, snd += next;
                }
                cout << fst << " " << snd << endl;
               

            }
            fclose(fi);
        }
        else
        {
            printf("Fail open file\n");
        }

    }


    void Problem1_4()
    {
        auto begin = chrono::high_resolution_clock::now();
        Run_Problem1_4("D:\\Training\\github\\hello-world\\reference\\Sample\\2016\\round1\\Problem4_set4\\input001.txt");
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout << "\n\n" << ms << " ms" << endl;//2 ms
    }
}
