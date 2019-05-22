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

        if (fi)
        {
            //cin >> T;
            fscanf(fi,"%d",&T);
            //printf("%d\n",T);
            for(int i =0; i < T; i++)
            {
                UINT32 price0 =0; //converted price of gas in intersect city
                UINT64 min_cost =0;//cost of trip from left to right
                UINT64 C =0; //cost from left to intersect on horizon
                UINT64 cost_H = 0; //cost when only travel on horizon

                 //cin >> N;
                  fscanf(fi,"%d",&N);
                 //printf("%d\n",N);
                 PH = new UINT32[N-1];
                 LH = new UINT32[N-1];

                 //read N-1 static of cities
                 for(int j =0; j < N-1;j++)
                 {
                    //cin >> PH[j];
                    //cin >> LH[j];
                    fscanf(fi,"%d",&PH[j]);
                    fscanf(fi,"%d",&LH[j]);
                    //printf("%d %d ",PH[j],LH[j]);
                 };


                 //cin >> p;
                 fscanf(fi,"%d",&p);
                 //printf("\n%d ",p);
                 //
                  UINT32 price =0;
                  for(int j =0; j < N-1;j++)
                  {

                    if(j == 0) price = PH[j];
                    if(price > PH[j])
                    {
                        price = PH[j];
                    }

                    if(j < p-1)  C += price * LH[j];
                    if(j == p-1) price0 = price;

                    cost_H += price * LH[j];//calculate when travel only on horizon
                  }

                  min_cost = cost_H;


                //cin >> M;//number of cities on Vertical
                fscanf(fi,"%d",&M);
                //printf("%d\n",M);
                LV = new UINT32[M];
                PV = new UINT32[M];

                UINT64 cost_V = 0;//cost when travel on vertical
                UINT64 down = 0;
                UINT64 down_length = 0;
                UINT32 price1 = price0;
                for(int k =0; k < M;k++)
                {
                    //cin >> LV[k];
                    //cin >> PV[k];
                    fscanf(fi,"%d",&LV[k]);
                    fscanf(fi,"%d",&PV[k]);
                    //printf("%d %d ",LV[k],PV[k]);
                    down += price1 * LV[k];
                    down_length += LV[k];
                    if(price1 > PV[k])
                    {
                        price1 = PV[k];
                    }
                    //travel k + 1 element on vertical then come back
                    if( C + down > min_cost) break;//no need to continue
                    cost_V = C + down + price1 * down_length;
                    //travel from intersect to right most
                    UINT32 price2 = price1;
                    for(int g = p -1; g < N-1;g++)
                    {
                        if(g == p -1)
                        {
                            cost_V += price2 * LH[g];
                        }
                        else
                        {
                            if(price2 > PH[g]) price2 = PH[g];
                            cost_V += price2 * LH[g];
                        }
                    }

                    if(min_cost > cost_V) min_cost = cost_V;


                }

                 //printf("\n");

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
        Run_Problem2_2("D:\\Training\\github\\data\\2016\\Round2\\Problem2\\set2\\input2.txt");
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout << "\n\n" << ms << " ms" << endl;//2 ms
    }
}
