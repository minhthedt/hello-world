#include "Common.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include<iostream>
using namespace std;

namespace Jam2018
{
    extern void split(const std::string &s, char delim, std::vector<std::string> &elems);
    extern std::vector<std::string> split(const std::string &s, char delim);


    void RunProblem1_3(const char* inputPath)
    {
        printf("Problem 3: %s\n",inputPath);
        auto begin = chrono::high_resolution_clock::now();

        unsigned short N = 0; //1 ≤ N ≤ 1000
        int currentLine = 0;
        stringstream stream;
        std::string line;
        ifstream myfile(inputPath);
        std::vector<unsigned short> dices;
        if (myfile.is_open())
        {
            while (!myfile.eof())
            {
                //read line
                getline(myfile, line);
                currentLine++;

                if (currentLine == 1)
                {
                    std::vector<std::string> words = split(line, ' ');
                    if (words.size() == 1)
                    {
                        N = atoi(words[0].c_str());
                    }
                    else
                    {
                        printf("Error input line 1");
                    }
                }
               

                if (currentLine == 2)
                {
                    std::vector<std::string> words = split(line, ' ');
                    if (words.size() == N)
                    {
                        for (int i = 0; i < N; i++)
                        {
                            dices.push_back(atoi(words[i].c_str()));
                        }
                       
                    }
                    else
                    {
                        printf("Error input line 2");
                    }
                }

            }

            myfile.close();
        }

        //sort 
        for (int i = 0; i < dices.size() - 1; i++)
        {
            for (int j = i + 1; j < dices.size(); j++)
            {
                if (dices[i] > dices[j])
                {
                    int temp = dices[i];
                    dices[i] = dices[j];
                    dices[j] = temp;
                }
            }
        }

        //find dices tower
        std::vector<unsigned short> tower;
        int num = 0;
        int detal = 0;
        int number0 = 0;
        for (int i = 0; i < dices.size(); i++)
        {
            if (dices[i] == 0)
            {
                number0++;
            }

            if (dices[i] < i - detal)
            {
                //for (int k = 0; k < tower.size(); k++)
                //{
                //    printf("%d ", tower[k]);
                //}
                //printf("\n");

                tower.clear();
                num++;
                detal = i;
            }

            tower.push_back(dices[i]);

            if (i == dices.size() - 1 && tower.size() > 0)
            {
                //for (int k = 0; k < tower.size(); k++)
                //{
                //    printf("%d ", tower[k]);
                //}
                //printf("\n");

                num++;
            }
        }

        if (number0 > 0 && num > number0)
        {
            int nosingle = num - number0;
            int single = number0 - 1;
            int max = nosingle > single ? nosingle : single;
            num = max + 1;
        }

        printf("num = %d\n", num);
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        std::cout << ms << " ms" << endl;
    }

    void Problem1_3()
    {
        RunProblem1_3(DATA_PROBLEM_2018_1_301);
        RunProblem1_3(DATA_PROBLEM_2018_1_310);
        RunProblem1_3(DATA_PROBLEM_2018_1_311);
        RunProblem1_3(DATA_PROBLEM_2018_1_312);
        RunProblem1_3(DATA_PROBLEM_2018_1_313);
        RunProblem1_3(DATA_PROBLEM_2018_1_314);
        RunProblem1_3(DATA_PROBLEM_2018_1_315);
        RunProblem1_3(DATA_PROBLEM_2018_1_3100);


    }

}
