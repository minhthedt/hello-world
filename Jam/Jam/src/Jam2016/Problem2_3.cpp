#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
#include <chrono>
using namespace std;

namespace Jam2016
{
#define UINT8 unsigned char
#define INT16 short int
#define UINT32 unsigned int
#define INT32  int
#define INT64 signed long long
#define UINT64 unsigned long long

    void Run_Problem2_3_TestCase(UINT32 a, UINT32 b,UINT32** m,UINT32 N)
    {

    }
    void Run_Problem2_3(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);
        UINT32 T; //number of test case T≤90
        UINT32 N; //N is the number of vertices 2≤N≤500
        UINT32 M; //M is the number of edges 1≤M≤10,000
        UINT32 K; //K is the number of queries. 1≤K≤3
        UINT32 i,j,w; //to represent the edge (i, j) and its length w.
        UINT32 a,b; //two different vertex numbers are given in a single line
        UINT32** m;//Adjacent matrix
        if(fi)
        {
            cin >> T;
            printf("%d\n",T);
            for(int t =0; t < T; t++)
            {
                cin >> N;cin >> M;cin >> K;
                printf("%d %d %d\n",N,M,K);
                m = new UINT32*[N];
                for(int p =0; p < N;p++)
                {
                    m[p] = new UINT32[N];
                    memset(m[p],0,N*sizeof(UINT32));
                }

                for(int h =0; h < M; h++)
                {
                    cin >> i;
                    cin >> j;
                    cin >> w;
                    m[i-1][j-1] = w;
                    printf("%d %d %d\n",i,j,w);
                }

                for(int k =0; k < K;k++)
                {
                    cin >> a;
                    cin >> b;
                    printf("%d %d\n",a,b);
                }

                Run_Problem2_3_TestCase(a-1,b-1,m,N);
                for(int g =0; g < N;g++)
                {
                    delete[] m[g];
                }
                delete[] m;
            }

            fclose(fi);
        }
    }

    void Problem2_3()
    {
        auto begin = chrono::high_resolution_clock::now();
        Run_Problem2_3("D:\\Training\\github\\data\\2016\\Round2\\Problem3\\set1\\00.in");
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout << "\n\n" << ms << " ms" << endl;//2 ms
    }
}
