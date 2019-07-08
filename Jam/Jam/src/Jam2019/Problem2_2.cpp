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

    
  


    void Run_Problem2_2_TestCase(const std::vector<INT64>& arr, UINT32 n, UINT32 num_zero)
    {
        UINT64 m = 0;//sum of all n elements
        for (int i = 1; i <= n; i++) m += arr[i];
        //from 0 -> sum have sum + 1 element
        //L[i,j] là số tập con của dãy 1..i, có tổng là j
        UINT64** L = new UINT64*[n +1];
        for (int i = 0; i <= n; i++)
        {
            L[i] = new UINT64[m + 1];
            memset(L[i],0,sizeof(UINT64)*(m+1));
            L[i][0] = 1;
        }
        UINT64* ptr1 = L[1];
        UINT64* ptr2 = L[2];
        UINT64* ptr3 = L[3];
        UINT64* ptr4 = L[4];
        UINT64* ptr = L[n];
        //tính L[i,j] với i{1->n}; j{1 -> m}
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                //L[i][j] = L[i - 1][j - arr[j]] + L[i - 1][j];
                //số lượng dãy con tạo bởi miền 1 -> i -1 có tổng là j - arr[i]; 
                //thêm phần tử arr[i] vào mỗi dãy con này để được dãy con mới thuộc L[i][j]
                INT64 L1 = 0;
                //số dãy con tạo bởi miền 1 -> i -1 có tổng là j,
                //những dãy con này đều thuộc L[i][j]
                INT64 L2 = 0;
                //Số lượng dãy con tạo bới miền 1 -> i -1 có tổng là j
                //arr[i] trùng với 1 phần tử của dãy con (tồn tại 1 <= x <= i-1 và arr[x] = arr[i];
                INT64 L3 = 0;

                INT64 x = j - arr[i];
                INT64 y = i - 1;
                
                if (x < 0) L1 = 0;
                else L1 = L[i - 1][ j - arr[i]];

                if (i - 1 == 0 && j > 0) L2 = 0;
                else L2 = L[i - 1][j];

                //duyet qua cac phan tu truoc do co value == arr[i]
                
                if (arr[i - 1] == arr[i])
                {
                    L[i][j] = L2 > L1 ? L2 : L1;
                }
                else
                {
                    L[i][j] = L1 + L2;
                }
                
            }
        }
       

        UINT64 total = 0;
        for (int i = 1; i <= m; i++)
        {
            if (checkValid(i)) total += ptr[i];
        }
        total *= (num_zero + 1);
        cout << total << "\n";
    }


    void Run_Problem2_2(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);
        if (fi)
        {
            UINT32 T; //number of testcase (1 ≤ T ≤ 10)
            UINT32 n; //size of one-demensional array 1 ≤ n ≤ 60
            std::vector<INT64> arr;//vector contain n element

            cin >> T;
            //printf("%d\n",T);
            for (int i = 0; i < T; i++)
            {
                cin >> n;
                //printf("%d\n", n);
                arr.resize(n+1);
                arr[0] = 0;
                for (int j = 1; j <= n; j++)
                {
                    cin >> arr[j];
                    //printf("%d ", arr[j]);
                }
                //printf("\n");

                //sort
                std::sort(arr.begin()+1, arr.end(), [](const UINT32 a, const UINT32 b) -> bool
                {
                    return a < b ? true : false;
                }
                );

                int num_zero = 0;
                while (arr[1] == 0)
                {
                    num_zero++;
                    arr.erase(arr.begin() + 1);
                }

                Run_Problem2_2_TestCase(arr,n - num_zero, num_zero);
            }

            fclose(fi);
        }
    }

    void Problem2_2()
    {
        Run_Problem2_2("D:\\Training\\github\\hello-world\\reference\\Sample\\2019\\round2\\2nd_B\\subtask2\\P5-data-002.in");
        //Run_Problem2_2("D:\\Training\\github\\hello-world\\reference\\Sample\\2019\\round2\\problem2\\input001.txt");
    }
}