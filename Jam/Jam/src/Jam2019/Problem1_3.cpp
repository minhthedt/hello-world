#include "Common.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include<iostream>
#include <algorithm>
using namespace std;

namespace Jam2019
{
#define UINT8 unsigned char
#define INT16 short int
#define UINT32 unsigned int
#define INT64 long long int
#define UINT64 unsigned long long 

    enum Type : unsigned char
    {
        E_A,
        E_B,
        E_NONE
    };
    struct Element
    {
        UINT32 val;
        Type type;
        Element() :val(0), type(E_NONE) {};
        Element(UINT32 val, Type type) :val(val), type(type) {};
    };
    void RunProblem1_3(const char* inputPath)
    {

        FILE* fi = freopen(inputPath, "r", stdin);
        if (fi)
        {
            UINT32 T = 0;//number of test case
            UINT32 m, n;//size of array A,B: 1 <= n, m <= 10^6
            std::vector<Element> AB;//value 1 -> 10^9
            cin >> T;
            //printf("%d\n",T);
            for (UINT8 i = 0; i < T; i++)
            {
                UINT64 sum = 0;
                cin >> m; cin >> n;
                //printf("%d %d\n", m,n);
                AB.resize(m+n);
                for (int j = 0; j < m+n; j++)
                {
                    if(j < m) AB[j].type = E_A;
                    else AB[j].type = E_B;
                    cin >> AB[j].val; 
                    //printf("%d ", AB[j].val);
                    //if(j==m-1)  printf("\n");
                }
                //printf("\n");
               
                //sort
                std::sort(AB.begin(), AB.end(), [](const Element& a, const Element& b) -> bool
                {
                    return a.val < b.val;
                }
                );

                for (UINT32 k = 0; k < m + n; k++)
                {
                    if (AB[k].type == E_A)
                    {
                        int dex = k;
                        UINT32 tren = 0;
                        UINT32 duoi = 0;
                        while (dex < m + n - 1)
                        {
                            dex++;
                            if (AB[dex].type == E_B)
                            {
                                tren = AB[dex].val;
                                break;
                            }
                        }
                        dex = k;
                        while (dex > 0)
                        {
                            dex--;
                            if (AB[dex].type == E_B)
                            {
                                duoi = AB[dex].val;
                                break;
                            }
                        }

                        if (AB[k].val - duoi <= tren - AB[k].val && duoi != 0) sum += duoi;
                        else sum += tren;

                    }
                }
                cout << sum << std::endl;
            }

            fclose(fi);
        }
    }

    void Problem1_3()
    {
        RunProblem1_3("D:\\Training\\github\\hello-world\\reference\\Sample\\2019\\round1\\problem3\\input001.txt");
    }

}
