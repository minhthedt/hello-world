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
#define INT16 short int
#define UINT32 unsigned int
#define INT32  int
#define INT64 signed long long
#define UINT64 unsigned long long
#define PI  3.1415926535897932384626344
#define MAXN    100000



    bool isEven(char cnt[])
    {
        for (int i = 0; i < 26; i++)
        {
            if (cnt[i] & 1 )//cnt[i] đến số lượng ký tự i trong chuỗi
            {
                return false;
            }
        }
        return true;
    };
    void Run_Problem1_3(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);
         if(fi)
         {
            UINT32 T;
            cin >> T;
            char cnt[26];
            for (int i = 0; i < T; i++)
            {
                char* gs = new char[MAXN];
                memset(gs, 0, MAXN);
                cin >> gs;
                //printf("%s\n", gs);

                int size = strlen(gs);
                int ans = 0;
                //O(n^2) = ((N+1)*N/2)/2
                for (int i = 0; i < size - 1; i++)
                {
                    memset(cnt, 0, 26);
                    for (int j = i; j < size - 1; j+=2)
                    {
                        cnt[gs[j] - 'a']++;
                        cnt[gs[j+1] - 'a']++;
                        if (isEven(cnt))ans++;
                    }
                }

                cout << ans << std::endl;
            }
            fclose(fi);
        }
        else
        {
            printf("FAIL open %s\n",inputPath);
        }

    }

    void Problem1_3()
    {
        auto begin = chrono::high_resolution_clock::now();
        Run_Problem1_3("D:\\Training\\github\\hello-world\\reference\\Sample\\2016\\round1\\Problem3_set1\\inputT001.txt");
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout << "\n\n" << ms << " ms" << endl;//2 ms
    }
}
