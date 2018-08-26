#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
using namespace std;

namespace Jam2017
{
#define uint32 unsigned int

    void Run_Problem2_4(const char* inputPath)
    {
        printf("Problem 3: %s\n", inputPath);
        uint32 R, C, D, W;
        uint32** blocks;
        FILE *fi = fopen(inputPath, "r");

        fscanf(fi, "%d", &R);
        fscanf(fi, "%d", &C);
        fscanf(fi, "%d", &D);
        fscanf(fi, "%d", &W);

        blocks = new uint32*[R];
        for (int i = 0; i < R; i++)
        {
            blocks[i] = new uint32[C];
        }


        for (int i = 0; i < R; i++)
        {
            for (int j = 0; j < C; j++)
            {
                fscanf(fi, "%d", &blocks[i][j]);
            }
        }



        fclose(fi);


    }


    void Problem2_4()
    {
        //Run_Problem2_4(DATA_PROBLEM_2018_2_401);
        //Run_Problem2_4(DATA_PROBLEM_2018_2_410);
        //Run_Problem2_4(DATA_PROBLEM_2018_2_411);
        Run_Problem2_4(DATA_PROBLEM_2018_2_412);
        //Run_Problem2_4(DATA_PROBLEM_2018_2_413);

    }
}
