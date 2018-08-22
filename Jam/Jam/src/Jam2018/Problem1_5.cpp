#include "Common.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include<iostream>
#include <algorithm>
using namespace std;

namespace Jam2018
{
    extern void split(const std::string &s, char delim, std::vector<std::string> &elems);
    extern std::vector<std::string> split(const std::string &s, char delim);

    typedef enum
    {
        E_INCREASE =0,
        E_DECREASE,
        E_UNKNOW
    } STATE;
    void Run_Problem1_5(const char* inputPath)
    {
        STATE currentState = E_UNKNOW;
        std::vector<int> elements;
        int N = 0;
        FILE *fi = fopen(inputPath, "r");
       
        fscanf(fi, "%d", &N);
        int preHeight = 0; //1<=height<=100000
        int height = 0;
        int remark_index = 0;
        for (int i = 0; i < N; i++)
        {
            fscanf(fi, "%d", &height);
            elements.push_back(height);
            if (preHeight == 0)
            {
                currentState = E_UNKNOW;
            }
            else
            {
                STATE newState = E_UNKNOW;
                if (height >= preHeight) newState = E_INCREASE;
                else newState = E_DECREASE;

                if (currentState == E_UNKNOW)
                {
                    currentState = newState;
                }
                else
                {
                    if (currentState != newState)
                    {
                        currentState = newState;
                        remark_index = i;
                        elements.clear();
                        elements.push_back(height);
                    }
                }

            }
            preHeight = height;
        }

        fclose(fi);

        auto check = [](const std::vector<int>& arr)->bool
        {
            if (arr.size() > 0)
            {
                int first = arr[0];
                for (int i = 1; i < arr.size(); i++)
                {
                    if (first != arr[i]) return false;
                }
            }

            return true;
        };

        if (currentState == E_DECREASE )
        {
            printf("do steps = %d \n",N);
        }

        if (currentState == E_INCREASE)
        {
            if (!check(elements))
            {
                if (remark_index == 0)
                {
                    int steps = elements.size();
                    printf("do steps = %d \n", steps);
                }
                else
                {
                    int steps = remark_index + elements.size() + 3;
                    printf("do steps = %d \n", steps);
                }
                  

            }
            else
            {
                int steps = remark_index + elements.size() + 2;
                printf("do steps = %d \n", steps);
            }

           
        }
        
    }
    void Problem1_5()
    {
        Run_Problem1_5(DATA_PROBLEM_2018_1_501);
    }
}