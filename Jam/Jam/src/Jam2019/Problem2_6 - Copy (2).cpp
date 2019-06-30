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
        UINT32 x, y;

        UINT8* str = new UINT8[MAX_K + 1];//buffer contain string
        UINT8* ret = new UINT8[MAX_K + 1];
        UINT32* arr_x = new UINT32[MAX_M];//arrx[i] = x of opertaion i
        UINT32* arr_y = new UINT32[MAX_M];//arry[i] = y of opertaion i
        UINT64* arr_n = new UINT64[MAX_M];//arrn[i] =  size of subsequence after doing operation i

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
                //memset(arr_x,0, MAX_M *sizeof(UINT32));
                //memset(arr_y, 0, MAX_M * sizeof(UINT32));
                //memset(arr_n, 0, MAX_M * sizeof(UINT64));

                //memset(str, 0, MAX_K + 1);
                //memset(ret, 0, MAX_K + 1);
                //cin >> str;
                fscanf(stdin, "%s", str);
                //printf("%s\n", str);

                //count number of available operation
                UINT32 new_j = 0;
                for (int j = 0; j < m; j++)
                {
                    cin >> x;
                    cin >> y;
                    //printf("%d %d\n",x,y);
                    if (y < k)
                    {
                        x--;//appropriate with array
                        y--;//appropriate with array
                        arr_x[new_j] = x;
                        arr_y[new_j] = y;
                        if (new_j == 0)
                        {
                            arr_n[new_j] = n + y - x + 1;;
                        }
                        else
                        {
                            arr_n[new_j] = arr_n[new_j - 1] + y - x + 1;
                        }

                        new_j++;
                    }
                }

                m = new_j;

                UINT64 length = arr_n[m-1];
                if (length > k) length = k;
                ret[k] = '\0';
                for (INT64 j = length-1 ; j >= 0; j--)
                {
               
                    UINT64 idex = j;
                    bool invert = false;
                    INT64 op_id = m - 1;
                    UINT8 tmp = -1;
                    while (op_id > -2)
                    {
                        if (op_id == -1)
                        {
                            //return value or initial string
                            if (invert == false)
                            {
                                tmp =  str[idex];
                            }
                            else
                            {
                                tmp =  getInvert(str[idex]);
                            }

                        }
                        //backtrace of operation
                        UINT32 x = arr_x[op_id];
                        UINT32 y = arr_y[op_id];

                        //if (y > k - 1)
                        //{
                        //    //ignore operation op_id and run to op_id - 1
                        //    idex = idex;
                        //    op_id = op_id - 1;
                        //    continue;
                        //}
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

                        op_id = op_id - 1;
                        if (p[0] <= idex && idex <= p[1])
                        {
                            idex = idex;
                            continue;
                        }

                        if (p[2] <= idex && idex <= p[3])
                        {
                            idex = idex - (y - x + 1);
                            invert = !invert;
                            continue;
                        }

                        if (p[4] <= idex && idex <= p[5])
                        {
                            idex = idex - (y - x + 1);
                        }

                    }

                    ret[j] = tmp;
                    
                }
                
                cout << ret << "\n";
            }

            delete[] str;
            delete[] ret;
            delete[] arr_x;
            delete[] arr_y;
            delete[] arr_n;

            fclose(fi);
        }

       
    }

    void Problem2_6()
    {
        Run_Problem2_6("D:\\Training\\github\\hello-world\\reference\\Exam\\2019\\round2\\problem6\\input001.txt");
    }
}