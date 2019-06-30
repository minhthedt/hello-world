#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include<list> 
using namespace std;

namespace Jam2019
{
#define UINT8 unsigned char
#define INT16 short int
#define UINT32 unsigned int
#define INT32  int
#define INT64 long long int
#define UINT64 unsigned long long 


    // C++ implementation of Hopcroft Karp algorithm for 
    // maximum matching 
#define NIL 0 
#define INF INT_MAX 

    // A class to represent Bipartite graph for Hopcroft 
    // Karp implementation 
    class BipGraph
    {
        // m and n are number of vertices on left 
        // and right sides of Bipartite Graph 
        int m, n;

        // adj[u] stores adjacents of left side 
        // vertex 'u'. The value of u ranges from 1 to m. 
        // 0 is used for dummy vertex 
        list<int> *adj;

        // These are basically pointers to arrays needed 
        // for hopcroftKarp() 
        int *pairU, *pairV, *dist;

    public:
        BipGraph(int m, int n); // Constructor 
        void addEdge(int u, int v); // To add edge 

                                    // Returns true if there is an augmenting path 
        bool bfs();

        // Adds augmenting path if there is one beginning 
        // with u 
        bool dfs(int u);

        // Returns size of maximum matcing 
        int hopcroftKarp();
    };

    // Returns size of maximum matching 
    int BipGraph::hopcroftKarp()
    {
        // pairU[u] stores pair of u in matching where u 
        // is a vertex on left side of Bipartite Graph. 
        // If u doesn't have any pair, then pairU[u] is NIL 
        pairU = new int[m + 1];

        // pairV[v] stores pair of v in matching. If v 
        // doesn't have any pair, then pairU[v] is NIL 
        pairV = new int[n + 1];

        // dist[u] stores distance of left side vertices 
        // dist[u] is one more than dist[u'] if u is next 
        // to u'in augmenting path 
        dist = new int[m + 1];

        // Initialize NIL as pair of all vertices 
        for (int u = 0; u<m + 1; u++)
            pairU[u] = NIL;
        for (int v = 0; v<n + 1; v++)
            pairV[v] = NIL;

        // Initialize result 
        int result = 0;

        // Keep updating the result while there is an 
        // augmenting path. 
        while (bfs())
        {
            // Find a free vertex 
            for (int u = 1; u <= m; u++)

                // If current vertex is free and there is 
                // an augmenting path from current vertex 
                if (pairU[u] == NIL && dfs(u))
                    result++;
        }
        return result;
    }

    // Returns true if there is an augmenting path, else returns 
    // false 
    bool BipGraph::bfs()
    {
        queue<int> Q; //an integer queue 

                      // First layer of vertices (set distance as 0) 
        for (int u = 1; u <= m; u++)
        {
            // If this is a free vertex, add it to queue 
            if (pairU[u] == NIL)
            {
                // u is not matched 
                dist[u] = 0;
                Q.push(u);
            }

            // Else set distance as infinite so that this vertex 
            // is considered next time 
            else dist[u] = INF;
        }

        // Initialize distance to NIL as infinite 
        dist[NIL] = INF;

        // Q is going to contain vertices of left side only. 
        while (!Q.empty())
        {
            // Dequeue a vertex 
            int u = Q.front();
            Q.pop();

            // If this node is not NIL and can provide a shorter path to NIL 
            if (dist[u] < dist[NIL])
            {
                // Get all adjacent vertices of the dequeued vertex u 
                list<int>::iterator i;
                for (i = adj[u].begin(); i != adj[u].end(); ++i)
                {
                    int v = *i;

                    // If pair of v is not considered so far 
                    // (v, pairV[V]) is not yet explored edge. 
                    if (dist[pairV[v]] == INF)
                    {
                        // Consider the pair and add it to queue 
                        dist[pairV[v]] = dist[u] + 1;
                        Q.push(pairV[v]);
                    }
                }
            }
        }

        // If we could come back to NIL using alternating path of distinct 
        // vertices then there is an augmenting path 
        return (dist[NIL] != INF);
    }

    // Returns true if there is an augmenting path beginning with free vertex u 
    bool BipGraph::dfs(int u)
    {
        if (u != NIL)
        {
            list<int>::iterator i;
            for (i = adj[u].begin(); i != adj[u].end(); ++i)
            {

                // Adjacent to u 
                int v = *i;
                // Follow the distances set by BFS 
                if (dist[pairV[v]] == dist[u] + 1)
                {
                    // If dfs for pair of v also returns 
                    // true 
                    if (dfs(pairV[v]) == true)
                    {
                        pairV[v] = u;
                        pairU[u] = v;
                        return true;
                    }
                }

            }

            // If there is no augmenting path beginning with u. 
            dist[u] = INF;
            return false;
        }
        return true;
    }

    // Constructor 
    BipGraph::BipGraph(int m, int n)
    {
        this->m = m;
        this->n = n;
        adj = new list<int>[m + 1];
    }

    // To add edge from u to v and v to u 
    void BipGraph::addEdge(int u, int v)
    {
        adj[u].push_back(v); // Add u to vfs list. 
    }

    void Run_Problem2_5(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);

        UINT32 T;//number of testcase
        UINT32 N; //number of rider
        UINT32 M; //number of driver
        UINT32 x; //expected distance from rider
        UINT32 y, z; //expected distance of driver from y -> z

        UINT32* arrX;
        if (fi)
        {
            cin >> T;
            //printf("%d\n",T);
            for (int i = 0; i < T; i++)
            {
                cin >> N;
                cin >> M;
                BipGraph g(N, M);
                //printf("%d %d\n", N,M);
                arrX = new UINT32[N];

                for (int j = 0; j < N; j++)
                {
                    cin >> x;
                    arrX[j] = x;
                    //printf("%d ",x);
                }
                //printf("\n");

                for (int j = 0; j < M; j++)
                {
                    cin >> y;
                    cin >> z;
                    //printf("%d %d\n", y,z);
                    for (int k = 0; k < N; k++)
                    {
                        if (arrX[k] >= y && arrX[k] <= z)
                        {
                            g.addEdge(k+1, j+1);
                        }
                    }
                }
                
                UINT32 ret = g.hopcroftKarp();
                cout << ret << "\n";

                delete[] arrX;

            }
            fclose(fi);
        }
    }

    void Problem2_5()
    {
        Run_Problem2_5("D:\\Training\\github\\hello-world\\reference\\Exam\\2019\\round2\\problem5\\input001.txt");
    }
}