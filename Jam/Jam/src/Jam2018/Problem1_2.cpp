#include "Common.h"
#include <sstream> //string stream
#include <fstream> //file stream
#include <vector>
#include <chrono>
#include<iostream>
using namespace std;

namespace Jam2018
{
    void split(const string &s, char delim, vector<string> &elems) 
    {
        stringstream ss(s);
        string item;
        while (getline(ss, item, delim)) 
        {
            if (!item.empty())
            {
                elems.push_back(item);
            }
            
        }
    }


    vector<string> split(const string &s, char delim) 
    {
        vector<string> elems;
        split(s, delim, elems);
        return elems;
    }

    int getLocation(const int& N, const int& A, int K)
    {
        int min = 0, max = 0;
        bool needChange = false;
        if (A > 0 && K <= A)
        {
            min = 1;
            max = A;
            needChange = true;
        }

        if (A < 0 && K >= N + A + 1)
        {
            min = N + A + 1;
            max = N;
            needChange = true;
        }

        if (needChange)
        {
            return (max - (K - min));
        }

        return K;
    }

    void Run_Problem1_2(const char* inputPath)
    {
        printf("Run_Problem1_2 input = %s\n", inputPath);
        auto begin = chrono::high_resolution_clock::now();

        int N = 0, K = 0, M = 0;
        int currentLine = 0;
        string line;
        ifstream myfile(inputPath);
        if (myfile.is_open())
        {
            while (!myfile.eof())
            {
                //read line
                getline(myfile, line);
                currentLine++;
                //handle line
                if (currentLine == 1)
                {
                    std::vector<std::string> datas = split(line, ' ');

                    if (datas.size() == 3)
                    {
                        N = atoi(datas[0].c_str());
                        K = atoi(datas[1].c_str());
                        M = atoi(datas[2].c_str());
                        printf("N = %d K = %d M = %d\n",N,K,M);
                    }
                    else
                    {
                        printf("Error Input line1 \n");
                    }
                }

                if (currentLine == 2)
                {
                    //do nothing
                }

                if (currentLine > 2 && currentLine <= M + 2)
                {
                    std::vector<std::string> datas = split(line, ' ');
                    if (datas.size() == 1)
                    {
                        int A = atoi(datas[0].c_str());
                        K = getLocation(N,A,K);
                    }
                    else
                    {
                        printf("Error Input line%d \n", currentLine);
                    }
                }


            }


            printf("result = %d \n",K);
            myfile.close();
        }
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout << ms <<" ms"<< endl;
    };

    void Problem1_2()
    {
        Run_Problem1_2(DATA_PROBLEM_2018_1_201);
        Run_Problem1_2(DATA_PROBLEM_2018_1_210);
        Run_Problem1_2(DATA_PROBLEM_2018_1_211);
        Run_Problem1_2(DATA_PROBLEM_2018_1_212);
        Run_Problem1_2(DATA_PROBLEM_2018_1_213);
        Run_Problem1_2(DATA_PROBLEM_2018_1_214);
        Run_Problem1_2(DATA_PROBLEM_2018_1_215);
        Run_Problem1_2(DATA_PROBLEM_2018_1_2100);
    }
}