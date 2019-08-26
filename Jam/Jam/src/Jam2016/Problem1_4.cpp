#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
#include <chrono>
#include <math.h>
#include <utility>      // std::pair, std::make_pair
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

struct Data
{
    int city;
    int length;
    Data(int city,int length):city(city),length(length){};
};

struct City
{
    int id;
    City():id(-1){};
    std::vector<Data> parents;
    std::vector<Data> childs;
};
    void Run_Problem1_4(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);
        if (fi)
        {
            UINT32 T;//the number of testcase
            UINT32 N;//the number of cities 2 <= N <= 100 000
            UINT32 Q;//the number of question 1 <= Q <= 300 000

            char line[128];


            cin >> T;
            printf("%d\n",T);
            for (int i = 0; i < 1; i++)
            {
                cin >> N;
                printf("%d ",N);
                
                cin >> Q;
                printf("%d\n",Q);

                City* cities = new City[N+1];
                


                for(int j =2; j <= N;j++)
                {
                    int ct;
                    cin >> ct; //ct < j
                    int length =0;
                    cin >> length;
                    printf("%d %d\n",ct,length);
                    //set city j and ct connect together
                    cities[j].parents.push_back(Data(ct,length));
                    cities[ct].childs.push_back(Data(j,length));
                }
                

                int M = 0;
                for(int j =2; j <= N;j++)
                {
                    if(cities[j].childs.size() == 0)
                    {
                        M++;
                    }
                }

                for(int j =0; j < M; j++)
                {
                    int len;
                    cin >> len;
                    printf("%d\n",len);
                }

                //caculate shortest distance between 2 cities
                UINT32 distance = 0;
                for(int j =0; j < Q; j++)
                {
                    int c1,c2;
                    cin >> c1;
                    cin >> c2;
                    printf("%d %d\n",c1,c2);
                    std::vector<std::pair<int,int>> c1s;
                    std::vector<std::pair<int,int>> c2s;
                    int temp = c1;
                    int len1 = 0;
                    if(c1 == 1) c1s.push_back(std::make_pair(c1,0));
                    while(cities[temp].parents.size() != 0)
                    {
                        int plen = cities[temp].parents[0].length;
                        len1 += plen;
                        temp = cities[temp].parents[0].city;
                        c1s.push_back(std::make_pair(temp,len1));
                    }

                    temp = c2;
                    if(c2 == 1) c2s.push_back(std::make_pair(c2,0));
                    int len2 = 0;
                    while(cities[temp].parents.size() != 0)
                    {
                        //distance child to parent
                        int plen = cities[temp].parents[0].length;
                        len2 += plen;
                        temp = cities[temp].parents[0].city;
                        c2s.push_back(std::make_pair(temp,len2));
                    }

                    
                    for(int m =0; m < c1s.size();m++)
                    {
                        for(int n =0; n < c2s.size();n++)
                        {
                            if(c1s[m].first == c2s[n].first)
                            {
                                distance += c1s[m].second + c2s[n].second;
                                break;
                            }
                        }
                    }

                }

                printf("distance = %d\n",distance);

            }
            fclose(fi);
        }

    }


    void Problem1_4()
    {
        auto begin = chrono::high_resolution_clock::now();
        Run_Problem1_4("D:\\Training\\github\\hello-world\\reference\\Sample\\2016\\round1\\Problem4_set1\\input000.txt");
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout << "\n\n" << ms << " ms" << endl;//2 ms
    }
}
