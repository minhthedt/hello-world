#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
#include <algorithm>    // std::find
using namespace std;

namespace Jam2017
{
#define uint32 unsigned long long

    std::vector<char> specialChars = { '*','-','.' };
    std::vector<char> vowelChars = { 'a','e', 'i', 'o', 'u' };

    bool isSpecialChar(char ch)
    {
        auto it = std::find(specialChars.begin(), specialChars.end(),ch);
        if (it != specialChars.end()) return true;
        return false;
    }

    bool isConsecutiveSpecialChar(const char* chs)
    {
        if (isSpecialChar(chs[0]) && isSpecialChar(chs[1]) && isSpecialChar(chs[2]))
        {
            return true;
        }

        return false;
    }




    bool isVowelChar(char ch)
    {
        auto it = std::find(vowelChars.begin(), vowelChars.end(), ch);
        if (it != vowelChars.end()) return true;
        return false;
    }

    bool isConsecutiveVowelChar(const char* chs)
    {
        if (isVowelChar(chs[0]) && isVowelChar(chs[1]) && isVowelChar(chs[2]))
        {
            return true;
        }

        return false;
    }

    bool isSameChar(const char* chs)
    {
        if (chs[0] == chs[1] && chs[0] == chs[2])
        {
            return true;
        }
        return false;;
    }

    bool CheckValid(const char* word)
    {
        int length = strlen(word);

        if (length >= 3)
        {
            for (int i = 0; i <= length-3; i++)
            {
                if (isConsecutiveSpecialChar(&word[i])) return false;
                if (isConsecutiveVowelChar(&word[i])) return false;
                if (isSameChar(&word[i])) return false;
            }
        }

        if (isSpecialChar(word[0]) || isSpecialChar(word[length - 1]))
        {
            return false;
        }

        return true;
    }

    std::vector<char> characters;
    void CreateWords(const int length,char* const word, int index,uint32& count)
    {
        if (index == -1)
        {
            char* chrs = word;
            //for (int i = 0; i < length; i++) chrs--;
            if (CheckValid(chrs))
            {
                count++;
            }
            else
            {    
                //printf("word = %s\n", chrs);
            }
            return;
        }

        for (uint32 i = 0; i < characters.size(); i++)
        {
            word[index] = characters[i];
            if (index == 0 || index == length - 1)
            {
                if (!isSpecialChar(word[index]))
                {
                    CreateWords(length, word, index - 1, count);
                }
            }
            else
            {
                CreateWords(length, word, index - 1, count);
            }

        }
    }
    void Run_Problem2_5(const char* inputPath)
    {
        printf("Problem 5: %s\n", inputPath);
        uint32 a, b;

        FILE *fi = fopen(inputPath, "r");
        fscanf(fi, "%llu", &a);
        fscanf(fi, "%llu", &b);

       
        for (char ch = 'a'; ch <= 'z'; ch++)
        {
            characters.push_back(ch);
        }
        characters.push_back('*');
        characters.push_back('-');
        characters.push_back('.');

        uint32 count = 0;
        for ( uint32 i = a; i <= b; i++)
        {
            uint32 length = i;
            char* word = new char[length + 1];
            memset(word,0, length +1);
            CreateWords(length,word, length -1, count);
            delete[] word;
        }
        printf("count = %d \n", count);
        fclose(fi);


    }


    void Problem2_5()
    {
        //Run_Problem2_5(DATA_PROBLEM_2018_2_501);
        //Run_Problem2_5(DATA_PROBLEM_2018_2_510);
        Run_Problem2_5(DATA_PROBLEM_2018_2_511);
        //Run_Problem2_5(DATA_PROBLEM_2018_2_512);
        //Run_Problem2_5(DATA_PROBLEM_2018_2_513);

    }
}
