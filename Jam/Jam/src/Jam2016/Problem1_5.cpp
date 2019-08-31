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
#define INT16 signed short 
#define UINT16 unsigned short 
#define UINT32 unsigned int
#define INT32  signed int
#define INT64 signed long long
#define UINT64 unsigned long long
#define PI  3.1415926535897932384626344

    UINT64 getMax(INT32 N, UINT16 *P, UINT16 *S, UINT64 *sum)
    {
       
        sum[0] = 0;//have only 0 snake
        sum[1] = 0;//have only 1 snake
        //root -> N -> 1 -> root -1
        int ii = 0 , jj = 0;
        for (int i = 2; i <= N; i++)
        {
            if (sum[i] == 0) sum[i] = sum[i - 1];
          
            for (int j = i - 1; j >= 1; j--)
            {                
                //tính trường hợp snake tham gia phát điện
                if (S[j] != S[i])//khác giới
                {
                    UINT64 temp = P[i] * P[j] + sum[j - 1];
                    //sum[i] = sum[i] > temp ? sum[i] : temp;
                    if (sum[i] < temp)
                    {
                        sum[i] = temp;
                        ii = i;
                        jj = j;
                    }
                }

            }
            //printf("[%d] ii = %d jj = %d ----> %d\n",i, ii, jj, sum[i]);
        }
        //printf("%d\n", sum[N]);
        return sum[N];
    }

    void ShiftLeft(UINT16 *dt, UINT32 N)
    {
        //dt size N + 1
        UINT16 bk = dt[1];
        for (int i = 1; i <= N-1; i++)
        {
            dt[i] = dt[i + 1];
        }
        dt[N] = bk;
    };

    UINT64 getMaximumAmount(INT32 N, UINT16 *P, UINT16 *S, UINT64 *sum)
    {
        UINT64 max = 0;
        INT32 loop = N;
        while (loop > 0)
        {
            memset(sum, 0, (N + 1) * sizeof(UINT64));
            UINT64 temp = getMax(N, P, S, sum);
            max = max > temp ? max : temp;
            //shift left
            ShiftLeft(P, N);
            ShiftLeft(S, N);
            loop--;
        }
        return max;
    };

    void Run_Problem1_5(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);
        if (fi)
        {
            INT32 T; //T ≤ 300
            INT32 N;//1 ≤ N ≤ 2,000
            UINT16 *P;//1 -> 1000
            UINT16 *S;//0 or 1

            cin >> T;
            //printf("%d\n",T);
            UINT64 *sum;
            while(T--)
            {
                cin >> N;
                //printf("%d\n", N);
                P = new UINT16[N+1];
                S = new UINT16[N + 1];
                sum = new UINT64[N + 1];//sum[i] là tổng điện lớn nhất của 1 -> i snakes có thể tạo ra
                P[0] = -1;
                S[0] = -1;
                for (int i = 1; i <= N; i++)
                {
                    cin >> P[i];
                    //printf("%d ", P[i]);
                }
                //printf("\n");
                for (int i = 1; i <= N; i++)
                {
                    cin >> S[i];
                    //printf("%d ", S[i]);
                }
                //printf("\n");
                //giai toan bang quy hoach dong
                UINT64 max = getMaximumAmount(N, P, S, sum);
                
                delete[] P;
                delete[] S;
                delete[] sum;
                cout << max << std::endl;
            }

            fclose(fi);

        }
    };

    void Problem1_5()
    {
        auto begin = chrono::high_resolution_clock::now();
        Run_Problem1_5("D:\\Training\\github\\hello-world\\reference\\Sample\\2016\\round1\\Problem5_set1\\input000.txt");
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout << "\n\n" << ms << " ms" << endl;//2 ms
    }
}
