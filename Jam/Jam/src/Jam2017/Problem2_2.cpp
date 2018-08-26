#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
using namespace std;

namespace Jam2017
{


    void Run_Problem2_2(const char* inputPath)
    {
        printf("Problem 2: %s\n", inputPath);
        int n,q,m;
        char method;
        FILE *fi = fopen(inputPath, "r");
       
        fscanf(fi, "%d", &n);
        fscanf(fi, "%d", &q);
        fscanf(fi, "%d", &m);

        char* arr_q =  new char[q];//contain array of operator // =0 (reverse) =1 (add)
        int* arr_i = new int[q]; //contain i number of reverse operartion
        int* arr_j = new int[q]; //contain j number of reverse operartion

        for (int h = 0; h < q; h++)
        {
            method = '0';
            while (method != 'a' && method != 'r')
            {
                fscanf(fi, "%c", &method);
            }
           
            if (method == 'a')
            {
                arr_q[h] = 'a';
            }
            else if (method == 'r')
            {
                arr_q[h] = 'r';

                int i, j;
                fscanf(fi, "%d", &i);
                fscanf(fi, "%d", &j);
                arr_i[h] = i;
                arr_j[h] = j;
            }
            else
            {
                printf("error format input line = %d\n",h);
            }
        }

        for (int h = 0; h < m; h++)
        {
            int indices;
            fscanf(fi, "%d", &indices);
            unsigned long long sum = 0;
            for (int k = q - 1; k >= 0; k--)
            {
                if (arr_q[k] == 'a') //add
                {
                    sum += indices;
                }
                else if (arr_q[k] == 'r') //reverse
                {
                    if (indices >= arr_i[k] && indices <= arr_j[k])
                    {
                        indices = arr_j[k] - (indices - arr_i[k]);
                    }
                }
            }
            
            printf("%d \n", sum);
        }


        fclose(fi);

        delete[] arr_q;
        delete[] arr_i;
        delete[] arr_j;
    }

    void Problem2_2()
    {
        Run_Problem2_2(DATA_PROBLEM_2018_2_201);
        Run_Problem2_2(DATA_PROBLEM_2018_2_210);
        Run_Problem2_2(DATA_PROBLEM_2018_2_211);
        Run_Problem2_2(DATA_PROBLEM_2018_2_212);
        Run_Problem2_2(DATA_PROBLEM_2018_2_213);

    }
}
