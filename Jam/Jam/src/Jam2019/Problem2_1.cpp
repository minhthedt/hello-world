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

    //(orgx,orgy) is center point of square
    //detal is distance from (orgx,orgy) to edge of square
    //example: square 3x3 => detal = 1
    void RotateSquare(INT32** arr, UINT32 orgx, UINT32 orgy, UINT32 delta,bool clockwise)
    {
        //determin 8 points on 1 square
        std::vector<INT32*> points(8, nullptr);
        points[0] = &arr[orgx - delta][orgy - delta];
        points[1] = &arr[orgx - delta][orgy];
        points[2] = &arr[orgx - delta][orgy + delta];
        points[3] = &arr[orgx][orgy + delta];
        points[4] = &arr[orgx+ delta][orgy + delta];
        points[5] = &arr[orgx + delta][orgy];
        points[6] = &arr[orgx + delta][orgy - delta];
        points[7] = &arr[orgx][orgy - delta];

        if (clockwise)
        {
            //backup
            INT32 point7 = *points[7];
            for (int i = 7; i > 0; i--)
            {
                *points[i] = *points[i - 1];
            }
            *points[0] = point7;
        }
        else
        {
            //counterclockwise
            INT32 point0 = *points[0];
            for (int i = 0; i < 7; i++)
            {
                *points[i] = *points[i + 1];
            }
            *points[7] = point0;
        }

    }
    void Run_Problem2_1(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);
        UINT32 T; //number of test case 1 ≤ T ≤ 10
        UINT32 n; //size of two-dimensional, integer array 1 ≤ n < 500
        INT32 d;  // a multiple of 45 0 ≤ |d| ≤ 360
        INT32** arr;
        if (fi)
        {
            cin >> T;
            //printf("%d\n",T);
            for (int i = 0; i < T; i++)
            {
                cin >> n;
                cin >> d;
                //printf("%d %d\n", n,d);

                arr = new INT32*[n];
                for (int j = 0; j < n; j++)
                {
                    arr[j] = new INT32[n];
                    for (int k = 0; k < n; k++)
                    {
                        cin >> arr[j][k];
                        //printf("%d ", arr[j][k]);
                    }
                    //printf("\n");
                }

                //rotate matrix
                bool clockwise = d > 0 ? true : false;
                UINT32 max_delta = (n - 1) / 2;
                for (int delta = 1; delta <= max_delta; delta++)
                {
                    for (int loop = 0; loop < std::abs(d)/45; loop++)
                    {
                        RotateSquare(arr, (n -1) / 2, (n - 1) / 2, delta, clockwise);
                    }
                }
               

                //print output
                for (int j = 0; j < n; j++)
                {
                    for (int k = 0; k < n; k++)
                    {
                        cout << arr[j][k] << " ";
                    }
                    cout << std::endl;
                    delete[] arr[j];
                }
                delete[] arr;
                arr = nullptr;
                
            }
            fclose(fi);
        }
    }

    void Problem2_1()
    {
        Run_Problem2_1("D:\\Training\\github\\hello-world\\reference\\Exam\\2019\\round2\\problem1\\input001.txt");
    }
}