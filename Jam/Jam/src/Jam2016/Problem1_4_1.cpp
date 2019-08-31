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
    
	//Cách xử lý thông thường, tính toán rất dư thừa và chậm chạp 
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

    std::vector<std::pair<int, int>> getParent(City* cities , int id_city)
    {
        std::vector<std::pair<int, int>> result;
        int temp = id_city;
        int len1 = 0;
        //push city đang xet với len = 0
        result.push_back(std::make_pair(id_city, 0));
        //push các parent, duyệt từ con lên gốc thì dừng
        while (cities[temp].parents.size() != 0)
        {
            int plen = cities[temp].parents[0].length;
            len1 += plen;
            temp = cities[temp].parents[0].city;
            result.push_back(std::make_pair(temp, len1));
        }

        return result;
    }

    //tìm khoảng cách các city qua tổ tiên chung gần nhất
    int getDistance1(City* cities, int c1, int c2,int& intersect)
    {
        std::vector<std::pair<int, int>> c1s = getParent(cities, c1);
        std::vector<std::pair<int, int>> c2s = getParent(cities, c2);

        int n1 = c1s.size()-1;
        int n2 = c2s.size()-1;
        while(true)
        {
            if(n1 < 0 || n2 < 0)
            {
                break;
            }

            if(c1s[n1].first == c2s[n2].first)
            {
                n1--;
                n2--;
            }else
            {
                break;
            }
        }

        return (c1s[n1+1].second + c2s[n2+1].second);
    }

    //tìm khoảng cách 2 city bằng con đường đi qua nút lá tới nút 1
    int getDistance2(City* cities, int c1, int c2, const std::vector<std::pair<int, int>>& leafs_len)
    {
        int min1 = 20000000;
        int min2 = 20000000;
        //đi tới city #1 qua leaf
        for (int i = 0; i < leafs_len.size(); i++)
        {
            int leaf = leafs_len[i].first;
            int length_leaf_to_1 = leafs_len[i].second;

             int intersect1 = -1;
             int intersect2 = -1;
             int dis1 = getDistance1(cities, c1, leaf, intersect1) + length_leaf_to_1;
             int dis2 = getDistance1(cities, c2, leaf, intersect2) + length_leaf_to_1;
            //nếu đường tới leaf đi qua 1, bỏ qua không xét
             if(intersect1 !=1) min1 = min1 < dis1 ? min1 : dis1;
             if(intersect2 !=1) min2 = min2 < dis2 ? min2 : dis2;
        }

        //đi tới city #1 không qua leaf
        int intersect;
        int x1 =  getDistance1(cities, c1,1,intersect);
        int x2 =  getDistance1(cities, c2,1,intersect);
        min1 = min1 < x1 ? min1 : x1;
        min2 = min2 < x2 ? min2 : x2;

        if(c1 == 1) min1 = 0;//không xét đi qua leaf
        if(c2 == 1) min2 = 0;//không xét đi qua leaf
        
        return  min1 + min2;
    }

    //need to improve in future
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
            //printf("%d\n",T);
            for (int i = 0; i < T; i++)
            {
                cin >> N;
                //printf("%d ",N);
                
                cin >> Q;
                //printf("%d\n",Q);

                City* cities = new City[N+1];
                for (int j = 1; j <= N; j++)
                {
                    cities[j].id = j;
                }


                for(int j =2; j <= N;j++)
                {
                    int ct;
                    cin >> ct; //ct < j
                    int length =0;
                    cin >> length;
                    //printf("%d %d\n",ct,length);
                    //set city j and ct connect together
                    cities[j].parents.push_back(Data(ct,length));
                    cities[ct].childs.push_back(Data(j,length));
                }
                

                std::vector<int> leafs;
                for(int j =2; j <= N;j++)
                {
                    if(cities[j].childs.size() == 0)
                    {
                        leafs.push_back(j);
                    }
                }

                //contain pair(leaf,distance from leaf to city #1)
                std::vector<std::pair<int, int>> leafs_len;
                for(int j =0; j < leafs.size(); j++)
                {
                    int len;
                    cin >> len;
                    leafs_len.push_back(std::make_pair(leafs[j],len));
                    //printf("%d\n",len);
                }

                //caculate shortest distance between 2 cities
                UINT32 distance1 = 0;
                UINT32 distance2 = 0;
                for(int j =0; j < Q; j++)
                {
                    int c1,c2;
                    cin >> c1;
                    cin >> c2;
                    //printf("%d %d\n",c1,c2);
                    int intersect = -1;
                    int tm1 = getDistance1(cities, c1, c2, intersect);;
                    distance1 += tm1;

                    //tinh khoang cach tu city #c1,#c2 -> #1 di qua cac nut leaf
                    int tm2 = getDistance2(cities, c1, c2, leafs_len);
                    distance2 += tm2 < tm1 ? tm2 : tm1;
                    int debug =0;

                }
                printf("%d %d\n", distance1, distance2);
               
                delete[] cities;
            }
            fclose(fi);
        }
        else
        {
            printf("Fail open file\n");
        }

    }


    void Problem1_4()
    {
        auto begin = chrono::high_resolution_clock::now();
        Run_Problem1_4("D:\\Training\\github\\hello-world\\reference\\Sample\\2016\\round1\\Problem4_set2\\input001.txt");
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout << "\n\n" << ms << " ms" << endl;//43s for Problem4_set2\\input001.txt
    }
}
