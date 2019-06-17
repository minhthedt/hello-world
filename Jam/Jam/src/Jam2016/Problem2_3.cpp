#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
#include <chrono>
#include <utility>      // std::pair
using namespace std;
//https://www.geeksforgeeks.org/dijkstras-algorithm-for-adjacency-list-representation-greedy-algo-8/
//[2019.02.06] the.vu: lời giải chưa tối ưu chỉ pass set1,set2, Fail set3
namespace Jam2016
{
    #define UINT8 unsigned char
    #define INT16 short int
    #define UINT32 unsigned int
    #define INT32  int
    #define INT64 signed long long
    #define UINT64 unsigned long long
    #define _INFINITY_  static_cast<UINT32>(-1)

    //Giá của 1 điểm là khoảng cách từ điểm đó đến gốc
    //p la diem duoc kiem tra
    //G la ma tran ke
    //N la so diem
    //S la array chua khoang cach den root
    //prev la array chua diem lien truoc
    //num la so point chua dc xet trong G
    //visited[i] =  true => i da duoc xet
    void Run_Problem2_3_Dijkstra(UINT32 p,  UINT32** G,  UINT32 N, UINT32* S, INT32* prev,bool* visited, UINT32 num)
    {
        //return khi đã xét tất cả các đỉnh
        if (num == 0) return;

        INT32 next = -1;//là đỉnh sẽ được xét trong vòng lặp tiếp theo
        UINT32 min = _INFINITY_;//giá nhỏ nhất của các đỉnh chưa được xét
        visited[p] = true;
        //duyệt qua tất cả các đỉnh
        for (int i = 0; i < N; i++)
        {
            //printf(" visited[%d]=%d G[%d][%d] = %d S[%d] = %d\n", i, visited[i], p, i, G[p][i], i, S[i]);
            //check đỉnh chưa được xét
            if (!visited[i])
            {
                //check các đỉnh liền kề với p
                if (G[p][i] > 0)
                {
                    //printf("S[%d]= %d  G[%d[%d]= %d \n", p, S[p],p,i, G[p][i]);
                    //khoảng cách từ đỉnh i đến gốc nếu đi qua đỉnh p
                    UINT32 tmp = S[p] + G[p][i];
                    if (S[i] > tmp)
                    {
                        //Gán lại giá cho đỉnh liền kề i vì đường đi qua p ngắn hơn
                        S[i] = tmp;
                        //printf("S[%d]= %d\n", i,tmp);
                        //lúc này đỉnh liền trước của i sẽ là p
                        prev[i] = p;
                    }
                }

                //tìm điểm có Giá nhỏ nhất chưa được xét
                if (min > S[i])
                {
                    next = i;
                    min = S[i];
                }
            }
        }

        //printf("next: S[%d] = %d\n", next, S[next]);
        Run_Problem2_3_Dijkstra(next, G, N, S, prev, visited, num-1);
    }


    std::vector<int> Run_Problem2_3_TestCase(UINT32 a, UINT32 b,UINT32** G,UINT32 N)
    {
        std::vector<int> result;
        UINT32* S = new UINT32[N];
        INT32* prev = new INT32[N];
        bool* visited = new bool[N];
        //S[i] la khoang cach tu diem i toi goc
        for (int i = 0; i < N; i++)
        {
            S[i] = _INFINITY_;
            prev[i] = -1;
            visited[i] = false;
        }
        S[a] = 0;
        //tính khoảng cách từ các điểm đến a
        Run_Problem2_3_Dijkstra(a, G, N, S, prev, visited, N);
        UINT32* S1 = new UINT32[N];
        for (int i = 0; i < N; i++)
        {
            S1[i] = _INFINITY_;
            prev[i] = -1;
            visited[i] = false;
        }
        S1[b] = 0;
        //tính khoảng cách từ các điểm đến b
        Run_Problem2_3_Dijkstra(b, G, N, S1, prev, visited, N);


        const UINT32 shortestPath = S[b];
        std::pair<UINT32, UINT32> edge(_INFINITY_, _INFINITY_);
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (G[i][j] > 0)//i và j nối nhau
                {
                    if (S[i] + S1[j] + G[i][j] == shortestPath)// i,j thuộc short path
                    {
                        if (S[i] < shortestPath * 0.5 &&  S1[j] < shortestPath * 0.5)
                        {
                            std::pair<UINT32, UINT32> temp = std::make_pair(min(i,j), max(i,j));
                            if (edge > temp) edge = temp;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < N; i++)
        {
            if (shortestPath % 2 == 0)
            {
                if (S[i] == shortestPath / 2 && S1[i] == shortestPath / 2)
                {
                    std::pair<UINT32, UINT32> temp = std::make_pair(i, i);
                    if (edge > temp) edge = temp;
                }
            }
        }


        result.push_back(edge.first+1);//increase 1 index
        result.push_back(edge.second+1);

        delete[] S;
        delete[] S1;
        delete[] prev;
        delete[] visited;
        return result;
    }
    void Run_Problem2_3(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);
        UINT32 T; //number of test case T≤90
        UINT32 N; //N is the number of vertices 2≤N≤500
        UINT32 M; //M is the number of edges 1≤M≤10,000
        UINT32 K; //K is the number of queries. 1≤K≤3
        UINT32 i,j,w; //to represent the edge (i, j) and its length w. 1 < w <10000
        UINT32 a,b; //two different vertex numbers are given in a single line
        UINT32** G;//Adjacent matrix
        std::vector<int> out;
        if(fi)
        {
            cin >> T;
            //printf("%d\n",T);
            int kk = 0;
            for(int t =0; t < T; t++)
            {
                cin >> N;cin >> M;cin >> K;
                //printf("%d %d %d\n",N,M,K);
                G = new UINT32*[N];
                for(int p =0; p < N;p++)
                {
                    G[p] = new UINT32[N];
                    memset(G[p],0,N*sizeof(UINT32));
                }

                for(int h =0; h < M; h++)
                {
                    cin >> i;
                    cin >> j;
                    cin >> w;
                    G[i-1][j-1] = w;
                    G[j-1][i-1] = w;
                    //printf("%d %d %d\n",i,j,w);
                }

                for(int k =0; k < K;k++)
                {
                    kk++;
                    cin >> a;
                    cin >> b;
                    //printf("%d %d\n",a,b);
                    std::vector<int> temp = Run_Problem2_3_TestCase(a - 1, b - 1, G, N);
                    out.insert(std::end(out), std::begin(temp), std::end(temp));
                }


                for(int g =0; g < N;g++)
                {
                    delete[] G[g];
                }
                delete[] G;
            }

            fclose(fi);
        }
        else
        {
            printf("ERROR: Not found file .in\n");
        }

        std::vector<int> expected;
        std::string outpath = inputPath;
        outpath = outpath.substr(0, outpath.length() - 3);
        outpath += ".out";
        fi = fopen(outpath.c_str(), "r");
        if (fi)
        {
            int temp;
            for (int i = 0; i < out.size(); i++)
            {
                fscanf(fi, "%d", &temp);
                expected.push_back(temp);
            }
            fclose(fi);
        }
        else
        {
            printf("ERROR: Not found file .out\n");
        }
        bool pass = true;
        for (int i = 0; i < out.size(); i++)
        {
            if (out[i] != expected[i])
            {
                pass = false;
                printf("line[%d] -> %d != %d\n",(i+2) / 2 , out[i], expected[i]);
            }
        }

        if (pass) printf("\PASS \n");
        else  printf("\FAIL \n");
    }

    void Problem2_3()
    {
        auto begin = chrono::high_resolution_clock::now();
        //Run_Problem2_3("D:\\Training\\github\\data\\2016\\Round2\\Problem3\\set1\\05.in");//98 ms
        //Run_Problem2_3("D:\\Training\\github\\data\\2016\\Round2\\Problem3\\set2\\05.in");//600 ms
        Run_Problem2_3("D:\\Training\\github\\data\\2016\\Round2\\Problem3\\set3\\05.in");//4300 ms
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout << "\n\n" << ms << " ms" << endl;//2 ms
    }
}
