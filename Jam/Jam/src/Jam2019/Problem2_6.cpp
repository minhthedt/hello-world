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

#define MAX_M 10000
#define MAX_K 1000000

    UINT8 getInvert(UINT8 ch)
    {
        if (ch == '0') return '1';
        if (ch == '1') return '0';
        printf("Exception\n");
    }

    UINT8 getValueByIndex(UINT64 idex, UINT32 op_id, UINT32* arr_x, UINT32* arr_y, UINT64* arr_n,UINT8* str, UINT32 k, bool invert)
    {
        if (op_id == -1)
        {
            //return value or initial string
            if (invert == false)
            {
                return str[idex];
            }
            else
            {
                return getInvert(str[idex]);
            }
            
        }
        //backtrace of operation
        UINT32 x = arr_x[op_id];
        UINT32 y = arr_y[op_id];

        //0->x-1
        //x->y
        //y+1 -> y+1 + (y-x)
        //y+1 + (y-x) + 1 -> arr_n[op_id] - 1 + (y-x) + 1;
        UINT64 p[8];
        p[0] = 0;
        p[1] = y;

        p[2] = y + 1;
        p[3] = y + 1 + (y - x);

        p[4] = y + 1 + (y - x) + 1;
        p[5] = arr_n[op_id] - 1 + (y - x) + 1;

        if (p[0] <= idex && idex <= p[1])
        {
            idex = idex;
            return getValueByIndex(idex, op_id - 1,arr_x,arr_y,arr_n,str, k, invert);
        }

        if (p[2] <= idex && idex <= p[3])
        {
            idex = idex - (y-x + 1);
            return getValueByIndex(idex, op_id - 1, arr_x, arr_y, arr_n, str, k, !invert);
        }

        if (p[4] <= idex && idex <= p[5])
        {
            idex = idex - (y - x + 1);
            return getValueByIndex(idex, op_id - 1, arr_x, arr_y, arr_n, str, k, invert);
        }

        printf("input error\n");
        return -1;
    };

    void Run_Problem2_6(const char* inputPath)
    {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        std::cout.tie(nullptr);

        FILE* fi = freopen(inputPath, "r", stdin);

        UINT32 T;//number of testcase
        UINT32 n;//size of original string 1 ≤ n ≤ 10^6
        UINT32 m;//number of operation 1 ≤ m ≤ 10^4
        UINT32 k;//size of output 1 ≤ k ≤ 10^6
        UINT8* str = new UINT8[MAX_K + 1];//buffer contain string
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

                memset(str, 0, MAX_K + 1);
                cin >> str;
                //printf("%s\n", str);

                UINT32 length = n;
                for (int j = 0; j < m; j++)
                {
                    cin >> x;
                    cin >> y;
                    //printf("%d %d\n",x,y);
                    UINT64 p[8];
                    p[0] = 0;
                    p[1] = y;

                    p[2] = y + 1;
                    p[3] = y + 1 + (y - x);

                    p[4] = y + 1 + (y - x) + 1;
                    p[5] = length - 1 + (y - x) + 1;

                    x--;//appropriate with array
                    y--;//appropriate with array
                    if (y < k)
                    {                       
                        //0 -> x-1
                        //x -> y
                        //y+1 -> y+1 + (y-x)
                        //y+1 + (y-x) + 1 -> length-1 + (y-x) + 1

                        if (k >= p[2] && k <= p[3])
                        {
                            int delta = k - (y + 1);
                            for (int i = x; i < x + delta; i++)
                            {
                                int index = i + (y - x) + 1;
                                str[index] = getInvert(str[i]);
                            }
                        }

                        if (k >= p[4] && k <= p[5])
                        {
                            for (int i = length - 1; i >= y + 1; i--)
                            {
                                int index = i + (y - x) + 1;
                                if (index < k)
                                    str[index] = str[i];
                            }
                        }

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

       
    }

    void Problem2_6()
    {
        Run_Problem2_6("D:\\Training\\github\\hello-world\\reference\\Exam\\2019\\round2\\problem6\\input001.txt");
    }
}