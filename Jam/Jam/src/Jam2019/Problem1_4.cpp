#include "Common.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include<iostream>
#include <algorithm>
#include <vector>
using namespace std;

namespace Jam2019
{
#define UINT8 unsigned char
#define INT16 short int
#define UINT32 unsigned int
#define INT64 long long int
#define UINT64 unsigned long long 
#define MODULO 1000000007

    UINT64 Calculate(const std::vector<UINT32>& x)
    {
        std::vector<UINT32> result;
        for (int i = 0; i < x.size(); i++)
        {
            if (i == 0)
            {
                result = std::vector<UINT32>(x[i], 1);
            }
            else
            {
                int x0 = result.size();
                int x1 = x[i];
                std::vector<UINT32> temp(x1,0);
                //tinh gia tri cho cac element cua temp
                for (int j = 0; j < x1; j++)
                {
                    if (j < x0)
                    {
                        for (int k = 0; k <= j; k++)
                        {
                            temp[j] += result[k];
                            temp[j] = temp[j] % MODULO;
                        }
                    }
                    else
                    {
                        temp[j] = temp[j - 1];
                    }

                }
                result = temp;
            }
        }

        UINT64 sum = 0;
        for (int i = 0; i < result.size(); i++)
        {
            sum += result[i];
        }
        return sum;
    }
    void Run_Problem1_4(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);
        if (fi)
        {
            UINT32 T;
            UINT32 n;//1 <= n <= 200
            std::vector<UINT32> x;//1 <= x[i] <= 200
            cin >> T;
            //printf("%d\n",T);
            for (int i = 0; i < T; i++)
            {
                cin >> n;
                x.resize(n);
                //printf("%d\n", n);
                for (int j = 0; j < n; j++)
                {
                    cin >> x[j];
                    //printf("%d ", x[j]);
                }
                //printf("\n");

                std::sort(x.begin(), x.end(), [](const UINT32& a, const UINT32& b)->bool
                {
                    return a < b;
                });

                UINT64 count = Calculate(x);;
                
                //printf("count = %llu\n",count*n % 1000000007);
                cout << count * n % 1000000007 << std::endl;
            }
          
            fclose(fi);
        }

    }

    void Problem1_4()
    {
        Run_Problem1_4("D:\\Training\\github\\hello-world\\reference\\Exam\\2019\\round1\\problem4\\input001.txt");

    }
}
