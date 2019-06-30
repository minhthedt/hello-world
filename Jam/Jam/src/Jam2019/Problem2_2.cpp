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

    std::vector<std::vector<UINT32>> trace_vec;

    bool checkValid(UINT32 num)
    {
        int num_odd_digits = 0;
        while (num > 0)
        {
            UINT8 module = num % 10;
            if (module % 2 != 0) num_odd_digits++;
            num = (num - module)/10;
        }

        if (num_odd_digits % 2 != 0) return true;
        return false;
    }

    
    void Run_Problem2_2_Recusive(const std::vector<UINT32>& arr,const UINT32 n, UINT32 root,UINT32 deep, UINT32& sum, UINT32& total, INT32* trace, const INT32 trace_deep)
    {
        trace[deep] = root;
        if (deep == 0)
        {
            if (checkValid(sum))
            {
                std::vector<UINT32> ret;
                ret.resize(trace_deep+1);

                for (int i = trace_deep; i >=0 ;i--)
                {
                    ret[i] = arr[trace[i]];
                    //printf("%d ", arr[trace[i]]);
                }
                //printf("\n");

                bool existed = false;
                for (int j = 0; j < trace_vec.size(); j++)
                {
                    int size = trace_deep + 1;
                    void* vec1 = trace_vec[j].data();
                    void* vec2 = ret.data();
                    if (memcmp(vec1, vec2,sizeof(UINT32)*size) == 0)
                    {
                        existed = true; 
                        break;
                    }
                }

                if (!existed)
                {
                    trace_vec.push_back(ret);
                    total++;
                }
            }
            return;
        }

       
        deep--;
        for (int i = root + 1; i < n - deep ; i++)
        {
            sum += arr[i];
            Run_Problem2_2_Recusive(arr, n, i, deep, sum,total,trace, trace_deep);
            sum -= arr[i];
        }
 
    }


    void Run_Problem2_2_TestCase(const std::vector<UINT32>& arr, UINT32 n)
    {
        //deep is size of subsequence 
        UINT32 total = 0;
        INT32* trace = new INT32[n];
        for (int i = 0; i < n; i++) trace[i] = -1;
        for (UINT32 deep = 0; deep < n; deep++)
        {           
            trace_vec.clear();
            for (UINT32 root = 0; root < n - deep; root++)
            {
                UINT32 sum = arr[root];
                INT32 trace_deep = deep;
               
                Run_Problem2_2_Recusive(arr,n, root,deep, sum, total,trace, trace_deep);
            }
        }

        delete[] trace;
        cout << total << std::endl;
    }


    void Run_Problem2_2(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);
        if (fi)
        {
            UINT32 T; //number of testcase (1 ≤ T ≤ 10)
            UINT32 n; //size of one-demensional array 1 ≤ n ≤ 60
            std::vector<UINT32> arr;//vector contain n element

            cin >> T;
            //printf("%d\n",T);
            for (int i = 0; i < T; i++)
            {
                cin >> n;
                //printf("%d\n", n);
                arr.resize(n);
                for (int j = 0; j < n; j++)
                {
                    cin >> arr[j];
                    //printf("%d ", arr[j]);
                }
                //printf("\n");

                //sort
                std::sort(arr.begin(), arr.end(), [](const UINT32 a, const UINT32 b) -> bool
                {
                    return a < b ? true : false;
                }
                );

                Run_Problem2_2_TestCase(arr,n);
            }

            fclose(fi);
        }
    }

    void Problem2_2()
    {
        Run_Problem2_2("D:\\Training\\github\\hello-world\\reference\\Exam\\2019\\round2\\problem2\\input001.txt");
    }
}