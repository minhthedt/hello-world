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
#define PI  3.1415926535897932384626344

    void Run_Problem2_2(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);
        UINT32 T;//number of testcase
        UINT32 N;//number of cities on horizon
        UINT32 M;//number of cities on vertical
        UINT32 p;//position of intersect from left
        UINT32* PH = nullptr;//array contain price of cities on horizon
        UINT32* LH = nullptr;//array contain length between cities on horizon
        UINT32* LV = nullptr;//array contain length between cities on vertical
        UINT32* PV = nullptr;//array contain price of cities on horizon
        UINT32 S =0; //price of gas in intersect city
        UINT64 min_cost =0;//cost of trip from left to right
        UINT64 L =0;//length from intersect to right most
        //UINT64 SL= 0;//length from intersect to a city on vertical
        UINT64 C =0; //cost from left to intersect on horizon
        if (fi)
        {
            cin >> T;
            for(int i =0; i < T; i++)
            {
                 cin >> N;
                 PH = new UINT32[N-1];
                 LH = new UINT32[N-1];
                 for(int j =0; j < N-1;j++)
                 {
                    cin >> PH[j];
                    cin >> LH[j];
                    if(j >0)
                    {
                        if(PH[j] > PH[j-1]) PH[j] = PH[j-1];
                    }
                    min_cost += PH[j] * LH[j];//calculate when travel only on horizon
                 };


                 cin >> p;

                //calculate length from p to right most
                L =0;
                C =0;
                for(int k = 0; k < N-1;k++)
                {
                    if( k < p-1)
                    {
                        C  += PH[k] * LH[k];
                    }else{
                        L  += LH[k];
                    }

                }

                cin >> M;//number of cities on Vertical
                LV = new UINT32[M];
                PV = new UINT32[M];

                S = PH[p-1];
                UINT64 cost =0;
                UINT64 sum = 0;
                for(int gg =0; gg < M;gg++)
                {
                    cin >> LV[gg];
                    cin >> PV[gg];
                    if(gg ==0)
                    {
                         if(PV[g] > S) PV[g] = S;
                    }else{
                        if(PV[g] > S) PV[g] = PV[g-1];
                    }
                }

                for(int g =0; g < M;g++)
                {
                    if(g ==0)
                    {
                        cost = C + S* LV[g] + PV[g]*(LV[g] + L);
                    }else{
                        sum += LV[g-1];
                        cost += LV[g] * PV[g-1] + sum * (PV[g] - PV[g-1]) + PV[g] * LV[g];
                    }

                    if(cost < min_cost) min_cost = cost;
                }

                printf("%lld\n",min_cost);
                delete[] PH; PH = nullptr;
                delete[] LH; LH = nullptr;
                delete[] LV; LV = nullptr;
                delete[] PV; PV = nullptr;
            }


            fclose(fi);
        }



    }

    void Problem2_2()
    {
        auto begin = chrono::high_resolution_clock::now();
        Run_Problem2_2("D:\\Training\\github\\data\\2016\\Round2\\Problem2\\set1\\input1.txt");
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout << "\n\n" << ms << " ms" << endl;//2 ms
    }
}
