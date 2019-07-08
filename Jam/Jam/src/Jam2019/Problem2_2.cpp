#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
#include <vector>
using namespace std;
//https://vnoi.info/wiki/algo/dp/basic-problems
namespace Jam2019
{
#define UINT8 unsigned char
#define INT16 short int
#define UINT32 unsigned int
#define INT32  int
#define INT64 long long int
#define UINT64 unsigned long long 


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
        
        //tính L[i,j] với i{1->n}; j{1 -> m}
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                //Chuyển về bài toán quy hoạch động 
                //L[i][j] = số dãy con khác nhau có tổng là j tạo bởi tập phần tử miền 1 -> i
                //vì dãy ban đầu được xắp xếp tăng dần => các phần tử giống nhau sẽ đặt liền nhau
                //tim k sao cho arr[i-k] == arr[i-k+1] và arr[i-k] > arr[i-k-1]
                //=>trong khoảng 1 -> i, có k+1 phần tử có giá trị == arr[i]
                //L[i][j] sẽ bằng tổng của
                //L[i-k-1][j-arr[i]*0] số dãy con có không chứa phần tử nào có giá trị bằng arr[i]
                //L[i-k-1][j-arr[i]*1] số dãy con chứa 1 phần tử có giá trị bằng arr[i]
                //L[i-k-1][j-arr[i]*2] số dãy con chứa 2 phần tử có giá trị bằng arr[i]
                //...
                //L[i-k-1][j-arr[i]*(k+1)] số dãy con chứa k+1 phần tử có giá trị bằng arr[i]
                INT64 k = 0;
                INT64 temp = i;
                while (temp - 1 >= 1 && arr[temp] == arr[temp - 1])
                {
                    temp--;
                    k++;
                }

                for (int p = 0; p <= k+1; p++)
                {
                    if (i - k - 1 > 0)
                    {
                        if (j - arr[i] * p >= 0)
                        {
                            L[i][j] += L[i - k - 1][j - arr[i] * p];
                        }
                    }
                    else  if (i - k - 1 == 0 && j - arr[i] * p == 0)
                    {
                        L[i][j] += L[i - k - 1][j - arr[i] * p];
                    }
                }
            }
        }
       
        UINT64 total = 0;
        for (int i = 1; i <= m; i++)
        {
            if (checkValid(i)) total += L[n][i];
        }
        total *= (num_zero + 1);
        cout << total << "\n";

        for (int i = 0; i < n + 1; i++)
        {
            delete[] L[i];
        }

        delete[] L;
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
        Run_Problem2_2("D:\\Training\\github\\hello-world\\reference\\Sample\\2019\\round2\\2nd_B\\subtask2\\P5-data-010.in");
        //Run_Problem2_2("D:\\Training\\github\\hello-world\\reference\\Sample\\2019\\round2\\2nd_B\\subtask2\\P5-data-002.in");
        //Run_Problem2_2("D:\\Training\\github\\hello-world\\reference\\Sample\\2019\\round2\\problem2\\input001.txt");
    }
}