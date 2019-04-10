#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <chrono>
#include <string>

using namespace std;

namespace Jam2018
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

     uint32 GetOutPut(const char* inputPath)
    {
        FILE *fi = fopen(inputPath, "r");
        if(!fi)
        {
            printf("ERROR : %s",inputPath);
            return 0;
        }
        uint32 out;
        fscanf(fi, "%llu", &out);
        fclose(fi);
        return out;
    }


    bool CheckExistedFile(const std::string& filepath)
    {
        struct stat buffer;
        return (stat (filepath.c_str(), &buffer) == 0);
    };

    void list_dir(const std::string&  path,std::vector<std::string>& output)
    {
       struct dirent *entry;
       DIR *dir = opendir(path.c_str());

       if (dir == NULL) {
          printf("ERROR: %s",path.c_str());
          return;
       }

       while ((entry = readdir(dir)) != NULL)
       {
          std::string str = (const char*)entry->d_name;
          std::string filepath =path + "\\" + str;
           if(entry->d_type == DT_DIR)
           {
               if(str.compare(".") != 0 && str.compare(".."))
               {
                   //cout << entry->d_name << endl;
                   list_dir(filepath,output);
               }

           }
           else if(CheckExistedFile(filepath))
           {
                //printf("%s\n",filepath.c_str());
               std::string extension = "";
               if(str.length() > 3)
               {
                   extension = str.substr(str.length()-3,str.length());
               }

               if (extension.compare(".in") == 0)
               {
                 output.push_back(filepath);
               }
           }
       }
    };

    void Run_Problem2_5(const char* inputPath)
    {
        printf("Problem 5: %s\n", inputPath);
        uint32 a, b;

        FILE *fi = fopen(inputPath, "r");
        if(!fi)
        {
            printf("ERROR : %s",inputPath);
            return;
        }
        fscanf(fi, "%llu", &a);
        fscanf(fi, "%llu", &b);
        printf("%llu %llu \n",a,b);

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
        printf("output = %lld \n", count);
        fclose(fi);

        std::string outpath = inputPath;
        outpath = outpath.substr(0,outpath.length()-3);
        outpath += ".out";
        uint32 out = GetOutPut(outpath.c_str());
        if(out == count) printf("PASS\n");
    }



    void Problem2_5()
    {
        std::string folder = "D:\\Training\\github\\data\\2018_round2\\E";
        std::vector<std::string> output;
        list_dir(folder,output);
        printf("number of samples = %d\n",output.size());
        for(int i =0; i< output.size();i++)
        {
            characters.clear();
            //printf("%s\n",output[i].c_str());
             auto begin = chrono::high_resolution_clock::now();
            //Run_Problem2_5(DATA_PROBLEM_2018_2_501);
            //Run_Problem2_5("D:\\Training\\github\\data\\2018_round2\\E\\sample-3.in");
            Run_Problem2_5(output[i].c_str());
            //Run_Problem2_5(DATA_PROBLEM_2018_2_512);
            //Run_Problem2_5(DATA_PROBLEM_2018_2_513);

            auto end = chrono::high_resolution_clock::now();
            auto dur = end - begin;
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
            cout <<"\n"<< ms << " ms" << endl;//2 ms
        }

    }
}
