#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include<chrono>
using namespace std;
//https://www.hackerearth.com/practice/algorithms/graphs/graph-representation/practice-problems/algorithm/sort-the-sequence-d77d8f67/editorial/
//Bài toán khá đơn giản, số tam giác có cạnh màu giống nhau = tổng số tam giác - tổng số tam giác có cạnh màu khác nhau
//tổng số tam giác = tổ hợp chập 3 của n phần tử
//tính số tam giác có cạnh màu khác nhau
//ta sẽ tìm số tam giác có 3 đỉnh x,y,z sao cho (x,y) màu trắng, (x,z) màu đen = deg(x)*(n-deg(x)-1)
//1 tam giác có 2 cạnh đen + 1 cạnh trắng => tìm ra 2 cặp x,y,z thỏa mãn
//1 tam giác có 2 cạnh trắng + 1 cạnh đen => tìm ra 2 cặp x,y,z thỏa mãn
namespace Jam2019
{
#define UINT8 unsigned char
#define INT16 short int
#define UINT32 unsigned int
#define INT32  int
#define INT64 long long int
#define UINT64 unsigned long long 
#define MAX_N 5000

    void Run_Problem2_4(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);
        UINT32 T; //number of test case
        UINT32 N; //3 ≤ N ≤ 5,000
        UINT32 M; //1 ≤ M ≤ min(1, 000, 000, N ×(N - 1) / 2) - number of pair of alliances
        UINT32 x, y; //1 ≤ x < y ≤ N - numbers of tribes
        UINT64 S;//tổ hợp chập 3 của N
        UINT64* deg;//deg[i] là số alliance của tribe thứ i

        //int e = 4;
        //int ee = e * (e - 1) * (e - 2);
        if (fi)
        {
            cin >> T;
            //printf("%d \n",T);
            for (int i = 0; i < T; i++)
            {
                cin >> N;
                cin >> M;

                //S = N * (N - 1) * (N - 2); //warning: sai kết quả vì phép nhân bị tràn
                UINT64 N_ = N;
                S = N_ * (N_ - 1) * (N_ - 2)/6;

                deg = new UINT64[N + 1];
                memset(deg, 0, sizeof(UINT64)*(N + 1));
                //printf("%d %d\n",N,M);
                for (int j = 0; j < M; j++)
                {
                    cin >> x;
                    cin >> y;
                    deg[x]++;
                    deg[y]++;
                    //printf("%d %d\n",x,y);
                }

                UINT64 diff = 0;//number of tribes is not alliances
                for (int k = 1; k <= N; k++)
                {
                    //cout << deg[k] << "\n";
                    diff += deg[k] * (N  - 1 - deg[k]);
                }

                INT64 sum = S - diff/2;

                cout << sum << "\n";
                delete[] deg;
            }
            fclose(fi);
        }
    }

    void Problem2_4()
    {
        auto begin = chrono::high_resolution_clock::now();
        Run_Problem2_4("D:\\Training\\github\\hello-world\\reference\\Sample\\2019\\round2\\2nd_D\\subtask2\\P2-data-007.in");
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout << "\n\n" << ms << " ms" << endl;//4172 ms
    }
}