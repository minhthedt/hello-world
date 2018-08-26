#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
using namespace std;

namespace Jam2017
{

    int getMaxHands(int num_cards)
    {
        int max_n = std::min(num_cards / 5, 8);
        return max_n;
    }
    void Run_Problem2_1(const char* inputPath)
    {
        int n;
        const int MAX_HANDS = 8;
        FILE *fi = fopen(inputPath, "r");

        fscanf(fi, "%d", &n);
        int remain_card = 52 - n;
        int max_hands = getMaxHands(remain_card);

        //calculate number of card to get minimum n hand-fullhouse
        int arr[8];
        arr[0] = 13 * 2 + 1; //=27, min =1  // ((27 - 4 * min) - (13 -min)) / 2 > min
        arr[1] = 13 * 2 + 3; //=29, min =2   // 
        arr[2] = 13 * 2 + 5; //=31, min =3   // 
        arr[3] = 13 * 2 + 7; //=33, min =4   // 
        arr[4] = 13 * 2 + 9; //=35, min =5   // 
        arr[5] = 13 * 2 + 11; //=37, min =4   // 
        arr[6] = 45; //=41, min =4   // 
        arr[7] = 13 * 3 + 3; //=42, min =4   // 

        int min_hands = 0;// 8 - getMaxHands(n);//min_hands <= max_hands_n;
        for (int i = 0; i < 8; i++)
        {
            if (remain_card >= arr[i]) min_hands = i + 1;
        }


        printf("%d %d \n", min_hands, max_hands);
        fclose(fi);
    }
    
    void Problem2_1()
    {
        Run_Problem2_1(DATA_PROBLEM_2018_2_101);
        Run_Problem2_1(DATA_PROBLEM_2018_2_110);
        Run_Problem2_1(DATA_PROBLEM_2018_2_111);
        Run_Problem2_1(DATA_PROBLEM_2018_2_112);
        Run_Problem2_1(DATA_PROBLEM_2018_2_113);
       
    }
}
