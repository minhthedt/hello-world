#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
#include <vector>
using namespace std;

namespace Jam2019
{
    enum COLOR
    {
        BLACK = 0,
        WHITE
    };
    COLOR checkColor(int index)
    {
        int b = index % 16;
        if (b == 0) return BLACK;
        if (b > 8)
        {
            b = 25 - b;
        }

        if (b % 2 == 1) return BLACK;
        else return WHITE;
    }

    COLOR checkColor(char* text)
    {
        char ch = text[0];
        //printf("text[1] = %d\n", text[1]);
        int index = text[1] - 48;
        char c = 'A';
        for (char i = 0; i <  8; i++)
        {
            if (c + i == ch)
            {
                //printf("c = %c%d\n", c + i, index);
                if (i % 2 == 0)
                {
                    if (index % 2 == 1) return BLACK;
                    else return WHITE;
                }
                else
                {
                    if (index % 2 == 1) return WHITE;
                    else return BLACK;
                }
            }
        }
    }

    void Run_Problem1_1(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);
        int T = 0;
        char arr[3];
        int index;
        memset(arr,0,3);
        if (fi)
        {
            cin >> T;
            //fscanf(fi, "%d", &T);
            printf("%d\n",T);
            std::string input = "";
           
           
            for(int i =0; i < T;i++)
            {
                cin >> arr;
                //getline(cin, input);
                //fscanf(fi, "%s", arr);
                printf("%s ", arr);
                //fscanf(fi, "%d", &index);
                cin >> index;
                printf("%d\n", index);
                printf("%d %d\n", checkColor(arr), checkColor(index));
                if (checkColor(arr) == checkColor(index))
                {
                    cout << "YES" << std::endl;
                }else
                    cout << "NO" << std::endl;
            }

            fclose(fi);
        }
    
    };

    void Problem1_1()
    {
        Run_Problem1_1("D:\\Training\\github\\hello-world\\reference\\Exam\\2019\\round1\\problem1\\input001.txt");

    }
   
}