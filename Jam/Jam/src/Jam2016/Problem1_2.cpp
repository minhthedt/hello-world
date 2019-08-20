#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
#include <chrono>
#include <math.h>
using namespace std;
//Done subtask 1
//FAIL subtask 2
namespace Jam2016
{
#define UINT8 unsigned char
#define INT16 short int
#define UINT32 unsigned int
#define INT32  int
#define INT64 signed long long
#define UINT64 unsigned long long
#define PI  3.1415926535897932384626344


    int isSimilar(INT32* present1,INT32* present2,int N)
    {
        //check
        int similar = 0;
          for(int j =0; j < N; j++)
          {
                //printf("j=%d\n",j);
                bool pass = true;
                int dx =0;
                if(pass)
                {
                    for(int k = j; k < N; k++)
                    {
                        //printf("present1[%d] = %d present2[%d] = %d\n",k,present1[k],dx,present2[dx]);
                        if(present1[k] != present2[dx])
                        {
                           pass = false;
                           break;
                        }
                        //printf("OK\n");
                        dx++;
                    }
                }

                if(pass)
                {
                    //printf("pass 2\n");
                    for(int k = 0; k < j; k++)
                     {
                        //printf("present1[%d] = %d present2[%d] = %d\n",k,present1[k],dx,present2[dx]);
                        if(present1[k] != present2[dx])
                        {
                            pass = false;
                            break;
                        }
                        dx++;
                        //printf("dx = %d\n",dx);
                     }
                }

                if(pass)
                {
                    similar = 1;
                    break;
                }

          }

          return similar;
    };

    int checkSimilar(INT32* present1,INT32* present2,int N)
    {
        //invert right -> left
          bool similar = isSimilar(present1,present2,N);
          int n1 = present1[N-1];
          for(int j = N-1; j >=0; j--)
          {
              if(j == 0)
              {
                  present1[0] =  -1 * abs(present1[0]) * n1/abs(n1);
              }else
              {
                  present1[j] =  -1 * abs(present1[j]) * present1[j-1]/abs(present1[j-1]);
              }
          }

          if(similar == 0) similar = isSimilar(present1,present2,N);
          //invert order
          for(int j=0; j < N/2;j++)
          {
              int temp = present2[j];
              present2[j] = present2[N-1-j];
              present2[N-1-j] = temp;
          }

          if(similar == 0)
          {
              similar = isSimilar(present1,present2,N);
          }

          return similar;
    }
    void Run_Problem1_2(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);
        if (fi)
        {
            UINT32 T;
            UINT32 N;//the number N of corners 4 ≤ N ≤ 100,0000
            cin >> T;//T <= 65
            printf("T = %d\n",T);
            INT32* present1 = nullptr;
            INT32* present2 = nullptr;
            for (int i = 0; i < T; i++)
            {
                  cin >> N;
                  present1 = new INT32[N];
                  present2 = new INT32[N];

                  for(int j =0; j < N; j++)
                  {
                      cin >> present1[j];
                  }

                  for(int j =0; j < N; j++)
                  {
                      cin >> present2[j];
                  }

                  //compare 2 arrays
                  int similar = checkSimilar(present1,present2,N);
                  cout << similar << std::endl;

                  delete[] present1;
                  delete[] present2;
            }
            fclose(fi);
        }else
        {
           std::cout << "open file FAIL" << inputPath;
        }

    }

    void Problem1_2()
    {
        auto begin = chrono::high_resolution_clock::now();
        Run_Problem1_2("D:\\Training\\github\\hello-world\\reference\\Sample\\2016\\round1\\Problem2_set2\\input002.txt");
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout << "\n\n" << ms << " ms" << endl;//2 ms
    }
}
