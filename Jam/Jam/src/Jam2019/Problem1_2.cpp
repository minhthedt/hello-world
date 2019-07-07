#include "Common.h"
#include <sstream> //string stream
#include <fstream> //file stream
#include <vector>
#include <chrono>
#include<iostream>
using namespace std;

namespace Jam2019
{
    #define INT16 short int
    #define INT64 long long int

    struct TestCase
    {
        INT16 N;
        INT16** A;
        INT64* sum_row;
        INT64* sum_col;
        TestCase() :N(0), A(nullptr) {};
        void AddOperation(INT16 r1, INT16 c1, INT16 r2, INT16 c2, INT16 val)
        {
            r1--; c1--; r2--; c2--;
            for (INT16 i = r1; i <= r2; i++)
            {
                sum_row[i] += (c2 - c1 + 1) * val;
                
            }
            for (INT16 j = c1; j <= c2; j++)
            {
                sum_col[j] += (r2 - r1 + 1) * val;
            }

        }

        void print()
        {
            for (INT16 i = 0; i < N; i++) cout << sum_row[i] << " ";
            cout << std::endl;
            for (INT16 i = 0; i < N; i++) cout << sum_col[i] << " ";
            cout << std::endl;
        }

        ~TestCase()
        {
            delete[] sum_row;
            delete[] sum_col;
            for (int i = 0; i < N; i++)
            {
                delete[] A[i];
            }
        }

    };

    void Run_Problem1_2(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);
        if (fi)
        {
            INT16 T = 0;
            INT16 N, M;
            cin >> T;
            //printf("%d\n",T);
            for (int i = 0; i < T; i++)
            {
                cin >> N;
                cin >> M;
                //printf("%d %d\n", N,M);
                TestCase test;
                test.N = N;
                test.A = new INT16*[N];
                test.sum_row = new INT64[N];
                test.sum_col = new INT64[N];
                memset(test.sum_row, 0, N*sizeof(INT64));
                memset(test.sum_col, 0, N * sizeof(INT64));
                for (INT16 j = 0; j < N; j++)//matrix NxN
                {
                    test.A[j] = new INT16[N];
                    for (INT16 k = 0; k < N; k++)
                    {
                        cin >> test.A[j][k];
                        test.sum_row[j] += test.A[j][k];
                        //printf("%d ", test.A[j][k]);
                    }
                    //printf("\n");
                }
                for (INT16 j = 0; j < N; j++)//matrix NxN
                {
                    for (INT16 k = 0; k < N; k++)
                    {
                        test.sum_col[j] += test.A[k][j];
                        //printf("%d ", test.A[j][k]);
                    }
                    //printf("\n");
                }
                //read M operation
                for (INT16 g = 0; g < M; g++)
                {
                    INT16 r1, c1, r2, c2, val;
                    cin >> r1; cin >> c1; cin >> r2; cin >> c2; cin >> val;
                    //printf("%d %d %d %d %d\n", r1, c1, r2,c2, val);
                    test.AddOperation(r1,c1,r2,c2,val);
                }               
                //printf("\n");
                test.print();
            }

            fclose(fi);
        }
    };

    void Problem1_2()
    {
        auto begin = chrono::high_resolution_clock::now();
        Run_Problem1_2("D:\\Training\\github\\hello-world\\reference\\Sample\\2019\\round1\\problem2\\input001.txt");
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout << "\n" << ms << " ms" << endl;//2 ms
    }
}