#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
#include <chrono>
#include <math.h>
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

    UINT32 Cal_Problem2_1(UINT32 Ox, UINT32 Oy, UINT32 n)
    {
        double R = Oy;
        double x = Ox;
        //double x = n / 2.0f;//lúc làm thực sự không hiểu đề bài, nghĩ rằng di chuyển đường tròn sao cho dây thừng nhỏ nhất

        double a2 = x * x + R * R;
        double b2 = (n - x)*(n - x) + R * R;
        double c2 = n * n;
        double cos = (a2 + b2 - c2) / (2 * sqrt(a2*b2));

        double alpha = acos(cos);
        double length = n + 2 * (PI - alpha) * R;

        return std::ceil(length);
    };

    void Run_Problem2_1(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);
        if (fi)
        {
            UINT32 K;//3 ≤ K ≤ 50
            UINT32 Ox, Oy, n;//1 ≤ Ox, Oy ≤ 100 and Ox < n < 500
            cin >> K;
            for (int i = 0; i < K; i++)
            {
                cin >> Ox;
                cin >> Oy;
                cin >> n;
                //printf("%d %d %d\n", Ox, Oy,n);
                UINT32 res = Cal_Problem2_1(Ox, Oy, n);
                printf("%d\n", res);//[2019.05.19] khong hieu vi sao ra ket qua ko giong Collab

            }
            fclose(fi);
        }

    }

    void Problem2_1()
    {
        auto begin = chrono::high_resolution_clock::now();
        Run_Problem2_1("D:\\Training\\github\\data\\2016\\Round2\\Problem1\\input1.txt");
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout << "\n\n" << ms << " ms" << endl;//2 ms
    }
}
