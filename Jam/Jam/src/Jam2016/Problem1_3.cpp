﻿#include "Common.h"
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



    void Run_Problem1_3(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);
        if (fi)
        {
            UINT32 T;
            cin >> T;
            for (int i = 0; i < T; i++)
            {


            }
            fclose(fi);
        }

    }

    void Problem1_3()
    {
        auto begin = chrono::high_resolution_clock::now();
        Run_Problem1_3("D:\\Training\\github\\hello-world\\reference\\Sample\\2016\\round1\\Problem2_set1\\input002.txt");
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout << "\n\n" << ms << " ms" << endl;//2 ms
    }
}
