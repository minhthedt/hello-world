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
#define MAX_ARRAY 100000


    void Run_Problem2_3_TestCase(const INT32* V,const UINT32 n, const UINT32 X, const UINT32 y, UINT32 Z,const INT32 MIN_IJ)
    {
        // MIN_IJ (min of j - i)
        // MAX_IJ (max of j - i)
        INT32 MAX_IJ = -1;
        if (y == 0)
        {
            MAX_IJ = n - 1;
        }
        else
        {
            MAX_IJ = X / y - 1;
        }

        if (MAX_IJ >= 0)
        {
            for (INT32 delta = MIN_IJ; delta <= MAX_IJ; delta++)
            {
                INT64 sum = 0;
                for (INT32 k = n - 1; k >= 0; k--)
                {
                    if (k - delta >= 0)
                    {
                        if (k == n - 1)
                        {
                            for (int m = k; m >= k - delta; m--)
                            {
                                sum += V[m];
                            }
                        }
                        else
                        {
                            sum += V[k - delta];
                            sum -= V[k + 1];
                        }

                        //check 2 conditions
                        if (sum - y * (delta + 1) >= Z)
                        {
                            if (y * (delta + 1) <= X)
                            {
                                //increase 1 as format output
                                cout << k - delta + 1 << " " << k + 1 << std::endl;
                                return;
                            }
                        }
                    }

                }
            }
        }

        cout << "-1" << std::endl;
    }

    void Run_Problem2_3(const char* inputPath)
    {

        FILE* fi = freopen(inputPath, "r", stdin);
        UINT32 T; //number of testcase 1 ≤ T ≤ 10)
        UINT32 n;//1 ≤ n ≤ 100,000
        UINT32 X, y, Z; //0 ≤ X, y, Z ≤ 109
        INT32* V = new INT32[MAX_ARRAY]; // | V[i] | ≤ 10^6.

        if (fi)
        {
            cin >> T;
            //printf("%d\n",T);
            for (int i = 0; i < T; i++)
            {
                cin >> n;
                cin >> X;
                cin >> y;
                cin >> Z;
                //printf("%d %d %d %d\n",n,X,y,Z);
                
                for (int j = 0; j < n; j++)
                {
                    cin >> V[j];
                    printf("%d ", V[j]);
                }
                //printf("\n");

                //decrease array
                INT32 MIN_IJ = 0;
                Run_Problem2_3_TestCase(V, n, X, y, Z, 0);
            }
            fclose(fi);
        }
        delete[] V;
    }

    void Problem2_3()
    {
        Run_Problem2_3("D:\\Training\\github\\hello-world\\reference\\Exam\\2019\\round2\\problem3\\input001.txt");
    }
}