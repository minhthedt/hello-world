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

    std::vector<std::pair<int, int>> getParent(City* cities , int id_city)
    {
        std::vector<std::pair<int, int>> result;
        int temp = id_city;
        int len1 = 0;
        //if (id_city == 1) result.push_back(std::make_pair(id_city, 0));
        result.push_back(std::make_pair(id_city, 0));
        while (cities[temp].parents.size() != 0)
        {
            int plen = cities[temp].parents[0].length;
            len1 += plen;
            temp = cities[temp].parents[0].city;
            result.push_back(std::make_pair(temp, len1));
        }

        return result;
    }

    int getDistance1(City* cities, int c1, int c2,int& intersect)
    {
        if (c1 == c2) return 0;
        std::vector<std::pair<int, int>> c1s = getParent(cities, c1);
        std::vector<std::pair<int, int>> c2s = getParent(cities, c2);

        for (int m = 0; m < c1s.size(); m++)
        {
            for (int n = 0; n < c2s.size(); n++)
            {
                if (c1s[m].first == c2s[n].first)
                {
                    intersect = c1s[m].first;
                    return (c1s[m].second + c2s[n].second);
                }
            }
        }

        return -1;
    }

    int getDistance2(City* cities, int c1, int c2, const std::vector<std::pair<int, int>>& leafs_len)
    {
        int min1 = 20000000;
        int min2 = 20000000;
        //tim cac duong ngan nha toi cac leaf
        for (int i = 0; i < leafs_len.size(); i++)
        {
            int leaf = leafs_len[i].first;
            int length_leaf_to_1 = leafs_len[i].second;
            int intersect = -1;

            int distance1 =getDistance1(cities, c1, leaf, intersect) + length_leaf_to_1;
            if (intersect != 1 && c1 != leaf) min1 = min1 < distance1 ? min1 : distance1;

            int distance2 = getDistance1(cities, c2, leaf, intersect) + length_leaf_to_1;            
            if (intersect != 1 && c2 != leaf) min2 = min2 < distance2 ? min2 : distance2;
        }

        if (c1 == 1) min1 = 0;
        if (c2 == 1) min2 = 0;
        //c1 di den c2 qua leaf va gap nhau tai city 1
        return  min1 + min2;
    }

    int findDistanceLeaftoCity1(int id_leaf, const std::vector<std::pair<int, int>>& leafs_len)
    {
        for (int i = 0; i < leafs_len.size(); i++)
        {
            auto& pair = leafs_len[i];
            if (pair.first == id_leaf) return pair.second;
        }

        return -1;
    }
    void getDistanceTo_City1_via_leaf(City* cities, int N, int id_city,int length, const std::vector<std::pair<int, int>>& leafs_len, int& output)
    {
        if (cities[id_city].childs.size() == 0)
        {
            length += findDistanceLeaftoCity1(id_city, leafs_len);
            output = output > length ? length : output;
        }

        for (int i = 0; i < cities[id_city].childs.size(); i++)
        {
            int id_child = cities[id_city].childs[i].city;
            length += cities[id_city].childs[i].length;
            getDistanceTo_City1_via_leaf(cities,N, id_child, length, leafs_len, output);
        }
    }

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
            for (int i = 0; i < T; i++)
            {
                cin >> N;
                printf("%d ",N);
                
                cin >> Q;
                printf("%d\n",Q);

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
                    printf("%d %d\n",ct,length);
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
                    printf("%d\n",len);
                }

                //caculate shortest distance between 2 cities
                UINT32 distance1 = 0;
                UINT32 distance2 = 0;
                for(int j =0; j < Q; j++)
                {
                    int c1,c2;
                    cin >> c1;
                    cin >> c2;
                    printf("%d %d\n",c1,c2);
                    int intersect = -1;
                    int tm1 = getDistance1(cities, c1, c2, intersect);;
                    distance1 += tm1;

                    //tinh khoang cach tu city #c1,#c2 -> #1 di qua cac nut leaf
                    int tm2 = getDistance2(cities, c1, c2, leafs_len);
                    distance2 += tm2 < tm1 ? tm2 : tm1;
                    

                }
                printf("distance1 = %d distance2 = %d\n", distance1, distance2);
               

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
        Run_Problem1_4("D:\\Training\\github\\hello-world\\reference\\Sample\\2016\\round1\\Problem4_set1\\input001.txt");
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout << "\n\n" << ms << " ms" << endl;//2 ms
    }
}
