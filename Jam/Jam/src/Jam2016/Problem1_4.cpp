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

    //cài đặt thuật toán dijkstra
    void dijkstra_shortest_path(unordered_map<int, unordered_map<int, int>>& edges, vector<int>& length, int src)
    {
        length[src] = 0;
        priority_queue <pair<int, int>> pq;
        //(make_pair(distance city to src, city)
        pq.push(make_pair(0, src));
        while (!pq.empty()) {
            int cost = -pq.top().first;
            int here = pq.top().second;
            pq.pop();
            if (length[here] < cost) continue;
            //duyệt các cạnh liền kề với here
            for (auto i : edges[here]) {
                int there = i.first;//city "there" kết nối với city "here"
                int nextDist = cost + i.second;//tính ra distance từ there tới src nếu đi qua here
                if (length[there] > nextDist) {
                    length[there] = nextDist;//gán lài distance cho there
                    pq.push(make_pair(-nextDist, there));
                }
            }
        }
    }
    
    void Run_Problem1_4(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);
        if (fi)
        {
            int testcase, n, q, a, b, m;
            cin >> testcase;
            //printf("%d\n",T);
            while(testcase--)
            {
                cin >> n;
                //printf("%d ",N);
                cin >> q;
                //printf("%d\n",Q);
                // Tree construction before adding roads.

                //unordered_map<city1, unordered_map<city2, length>> tree;
                unordered_map<int, unordered_map<int, int>> tree;
                for (int i = 2; i <= n; i++) 
                {
                    cin >> a >> b;
                    tree[i][a] = tree[a][i] = b;
                }

                // Construct a graph by adding roads.
                unordered_map<int, unordered_map<int, int>> graph(tree);
                for (int i = 2; i <= n; i++) {
                    //nếu chỉ có 1 kết nối (nút lá)
                    if (graph[i].size() == 1) {
                        cin >> m;
                        //nếu không connect với city #1 hoặc chiều dài kết nối với city #1 > m
                        if (graph[i].find(1) == graph[i].end() || graph[i][1] > m)
                            graph[i][1] = graph[1][i] = m;//gán lại giá trị
                    }
                }

                long long fst = 0, snd = 0;
                for (int i = 0; i < q; i++) {
                    cin >> a >> b;
                    vector<int> plen1(n + 1, 10000000), nlen2(n + 1, 10000000);
                    //tìm khoảng cách từ a đến tất cả các nút còn lại
                    dijkstra_shortest_path(tree, plen1, a);
                    dijkstra_shortest_path(graph, nlen2, a);
                    fst += plen1[b], snd += nlen2[b];
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
        Run_Problem1_4("D:\\Training\\github\\hello-world\\reference\\Sample\\2016\\round1\\Problem4_set2\\input001.txt");
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout << "\n\n" << ms << " ms" << endl;//2 ms
    }
}
