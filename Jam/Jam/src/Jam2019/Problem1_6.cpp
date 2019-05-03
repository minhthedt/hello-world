#include "Common.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>
#include <chrono>
#include<iostream>
#include <algorithm>
#include <stack>
#include <map>
#include <functional>
using namespace std;

namespace Jam2019
{
#define UINT8 unsigned char
#define INT16 short int
#define UINT32 unsigned int
#define INT32  int
#define INT64 signed long long 
#define UINT64 unsigned long long 

    int CompareKey(const std::string& key1, const std::string& key2)
    {
        if (key1.length() < key2.length())
        {
            return -1;
        }
        else if (key1.length() > key2.length())
        {
            return 1;
        }
        else
        {
            return key1.compare(key2);
        }
    }

    class compare {
    public:
        bool operator()(const std::string& key1, const std::string& key2) const 
        { 
            if (CompareKey(key1, key2) < 0) return true;
            else return false;
        }
    };

    struct Element
    {
        std::string key;
        INT32 value;
        Element() :value(0) {};
        Element(std::string key, INT32 value) :key(key),value(value) {};
    };
    struct Handler
    {
        INT64 sum;
        std::map<std::string, Element*> map;
        Handler() :sum(0) {};
        ~Handler()
        {
            for (auto it = map.begin(); it != map.end(); it++)
            {
                delete it->second;
            }
        }
        void Addition(std::string key, INT32 value)
        {
            auto search = map.find(key);
            if (search == map.end())
            {
                //add element
               map[key] = new Element(key, value);
            }
            else
            {
                search->second->value += value;
            }
            sum += value;
            cout << sum << " ";
        }

        void Purge(std::string key)
        {
            auto search = map.find(key);
            if (search != map.end())
            {
                sum -= search->second->value;
                //remove element
                delete search->second; 
                search->second = nullptr;
                map.erase(search);
            }
           
            cout << sum << " ";
        }

        void Sum(std::string key1, std::string key2)
        {
            std::string min, max;
            if (CompareKey(key1,key2) < 0)
            {
                min = key1; max = key2;
            }
            else
            {
                min = key2; max = key1;
            }

            INT64 tong = 0;
            for (auto it = map.begin(); it != map.end(); it++)
            {
                if (CompareKey(it->first,min) >= 0 && CompareKey(it->first, max) <= 0)
                {
                    tong += it->second->value;
                }
            }

            cout << tong << " ";
        }
 
    };

    void Run_Problem1_6(const char* inputPath)
    {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        FILE* fi = freopen(inputPath, "r", stdin);
        if (fi)
        {
          
            Handler handler;
            UINT32 n;//1 <= n <= 100,000
            cin >> n;
            //printf("%d\n",n);
            for (int i = 0; i < n; i++)
            {
               
                INT32 operation;
                cin >> operation;
                if (operation == 1)//add
                {
                    char* key = new char[100];// (10^99)-1
                    memset(key,0,100);
                    INT64 value;// -10^9 and 10^9
                    cin >> key;
                    cin >> value;
                    //printf("%d %s %lld\n", operation, key, value);
                    handler.Addition(key, value);
                    delete[] key;
                }
                else if (operation == 2)//sum
                {
                    char* key1 = new char[100];
                    char* key2 = new char[100];
                    memset(key1, 0, 100);
                    memset(key2, 0, 100);
                    cin >> key1;
                    cin >> key2;
                    //printf("%d %s %s\n", operation, key1, key2);
                    handler.Sum(key1, key2);
                    delete[] key1;
                    delete[] key2;
                }
                else  if (operation == 3)//Purge 
                {
                    char* key = new char[100];
                    memset(key, 0, 100);
                    cin >> key;
                    //printf("%d %s \n", operation, key);
                    handler.Purge(key);
                    delete[] key;

                }
                
               
            }
            fclose(fi);
        }
        
    };

    void Problem1_6()
    {
        Run_Problem1_6("D:\\Training\\github\\hello-world\\reference\\Exam\\2019\\round1\\problem6\\input002.txt");
    }
}