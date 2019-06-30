#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
#include <vector>
using namespace std;

namespace Jam2019
{
#define UINT8 unsigned char
#define INT16 short int
#define UINT32 unsigned int
#define INT32  int
#define INT64 long long int
#define UINT64 unsigned long long 
#define MILLION 1000000

    UINT8 getInvert(UINT8 ch)
    {
        if (ch == '0') return '1';
        if (ch == '1') return '0';
        printf("Exception\n");
    }
    void Run_Problem2_6(const char* inputPath)
    {

        FILE* fi = freopen(inputPath, "r", stdin);
        UINT32 T;//number of testcase
        UINT32 n;//size of original string 1 ≤ n ≤ 10^6
        UINT32 m;//number of operation 1 ≤ m ≤ 10^4
        UINT32 k;//size of output 1 ≤ k ≤ 10^6
        UINT8* str = new UINT8[MILLION+1];//buffer contain string
        UINT32 x, y;
        if (fi)
        {
            cin >> T;
            //printf("%d\n",T);
            for (int i = 0; i < T; i++)
            {               
                cin >> n;
                cin >> m;
                cin >> k;
                //printf("%d %d %d\n", n, m, k);

                memset(str, 0, sizeof(UINT8)*MILLION+1);
                cin >> str;
                //printf("%s\n", str);

                UINT32 length = n;
                for (int j = 0; j < m; j++)
                {
                    cin >> x;
                    cin >> y;
                    //printf("%d %d\n",x,y);
                    
                    x--;//appropriate with array
                    y--;//appropriate with array
                    if (y < k)
                    {
                        //0 -> x-1
                        //x -> y
                        //y+1 -> y+1 + (y-x)
                        //y+1 + (y-x) + 1 -> length-1 + (y-x) + 1

                        for (int i = length - 1; i >= y + 1; i--)
                        {
                            int index = i + (y - x) + 1;
                            if (index < k)
                                str[index] = str[i];
                        }

                        for (int i = x; i <= y; i++)
                        {
                            int index = i + (y - x) + 1;
                            str[index] = getInvert(str[i]);
                        }
                        //printf("result = %s\n", str);
                        length += y - x + 1;
                        if (length > k) length = k;
                    }
                    else
                    {
                        // y > MILLION will don't affect to output so don't check
                    }
                }

                cout << str << "\n";
                
            }

            fclose(fi);
        }

        delete[] str;
    }

    void Problem2_6()
    {
        Run_Problem2_6("D:\\Training\\github\\hello-world\\reference\\Exam\\2019\\round2\\problem6\\input001.txt");
    }
}