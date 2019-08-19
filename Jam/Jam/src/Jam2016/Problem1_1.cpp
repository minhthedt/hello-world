#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
#include <chrono>
#include <math.h>
#include <vector>
using namespace std;

namespace Jam2016
{
#define UINT8 unsigned char
#define INT16 short int
#define UINT32 unsigned int
#define INT32  int
#define INT64 signed long long
#define UINT64 unsigned long long
#define PI  3.1415926535897932384626344
//DONE subtask 1,2
//FAIL subtask 3
class Person
{
    public:
        INT32 id;
        Person* parent;
        std::vector<Person*> childs;

        Person():
            id(-1),parent(nullptr)
        {

        };
        Person(INT32 id_):
            id(id_),parent(nullptr)
        {
        }


    };

    void GetTreeDeep(Person* root, int deep,int& maxdeep)
    {
        if(root->childs.size() ==0)
        {
            maxdeep = maxdeep > deep ? maxdeep : deep;
        };

        for(int i =0; i < root->childs.size();i++)
        {
            GetTreeDeep(root->childs[i],deep+1,maxdeep);
        }
    };

    void GetTreeDeep(std::vector<Person*>& persons,int& maxdeep)
    {
        std::vector<Person*> leafs;
       for(int i =1; i < persons.size();i++)
       {
            if(persons[i]->childs.size() ==0)
            {
                leafs.push_back(persons[i]);
            }
       }

       for(int i =0; i < leafs.size();i++)
       {
           Person* leaf = leafs[i];
           int count =1;
           while(leaf->parent != nullptr)
           {
               count++;
               leaf = leaf->parent;
           }

           maxdeep = maxdeep > count ?  maxdeep : count;
       }
    };

    void Run_Problem1_1(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);
        if (fi)
        {

            UINT32 T;//T <= 45
            UINT32 N;//number of persons 2 ≤ N ≤ 50,000
            UINT32 a,b;//1 ≤ a, b ≤ N)
            Person* root = nullptr;
            cin >> T;
            //printf("%d\n",T);
            for (int i = 0; i < T; i++)
            {
                 cin >> N;
                 //printf("%d\n",N);
                 std::vector<Person*> persons;

                 for(int j =0; j <= N; j++)
                 {
                    persons.push_back(new Person(j));
                 };

                 for(int j =0; j < N-1;j++)
                 {
                    cin >> a;
                    cin >> b;
                    //printf("%d %d\n",a,b);
                    persons[a]->childs.push_back(persons[b]);
                    persons[b]->parent = persons[a];
                 };

                 for(int j =1; j <= N; j++)
                 {
                    if(persons[j]->parent == nullptr)
                    {
                        root = persons[j];
                        break;
                    }
                 };

                 int maxdeep =0;
                 GetTreeDeep(root,1,maxdeep);
                 //GetTreeDeep(persons,maxdeep);
                 std::cout <<  maxdeep << std::endl;
                  for(int j =0; j <= N; j++)
                 {
                    delete persons[j];
                 };
            }


            fclose(fi);
        }
        else
        {
           std::cout << "open file FAIL\n";
        }

    }

    void Problem1_1()
    {
        auto begin = chrono::high_resolution_clock::now();
        Run_Problem1_1("D:\\Training\\github\\hello-world\\reference\\Sample\\2016\\round1\\Problem1_set3\\input005.txt");
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout << "\n\n" << ms << " ms" << endl;//2 ms
    }
}
