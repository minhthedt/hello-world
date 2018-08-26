#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
using namespace std;

namespace Jam2017
{
#define uint64 unsigned int
    class Vertice
    {
    public:
        uint64 x, y;
        bool wasChecked;
        Vertice(uint64 x, uint64 y) : x(x), y(y), wasChecked(false) {};
        std::vector<Vertice*> childrens;
        void tryAddNode(Vertice* nd)
        {
            if (y == nd->x)
            {
                childrens.push_back(nd);
            }
        }
    };

    void Find(uint64 first, Vertice* root, uint64 depth, uint64& result)
    {
        root->wasChecked = true;
        if (depth == 0)
        {
            uint64 sum = first * root->y;
            result = result < sum ? sum : result;
            root->wasChecked = false;
            return;
        }

        std::vector<Vertice*> vertices = root->childrens;
        for (uint64 i = 0; i < vertices.size(); i++)
        {
            if (vertices[i]->wasChecked == false)
            {
                Find(first, vertices[i], depth - 1, result);
            }

        }

        root->wasChecked = false;
    }

    void Run_Problem2_3(const char* inputPath)
    {
        printf("Problem 3: %s\n", inputPath);
        uint64 n,x,y;
       
        FILE *fi = fopen(inputPath, "r");

        fscanf(fi, "%dll", &n);

        std::vector<Vertice*> vertices;
        vertices.reserve(n);

        for (uint64 i = 0; i < n; i++)
        {
            fscanf(fi, "%dll", &x);
            fscanf(fi, "%dll", &y);

            Vertice* node = new Vertice(x, y);
            for (uint64 j = 0; j < vertices.size(); j++)
            {
                vertices[j]->tryAddNode(node);
                node->tryAddNode(vertices[j]);
            }
            vertices.push_back(node);


            uint64 result = 0;
            for (uint64 k = 0; k < vertices.size(); k++)
            {
                Find(vertices[k]->x, vertices[k], vertices.size() - 1, result);
            }

            cout << result << endl;
        }

        printf("finish Problem 3\n");


        fclose(fi);

        for (uint64 i = 0; i < vertices.size(); i++)
        {
            delete vertices[i];
        }

    }


    void Problem2_3()
    {
        //Run_Problem2_3(DATA_PROBLEM_2018_2_301);
        //Run_Problem2_3(DATA_PROBLEM_2018_2_310);
        //Run_Problem2_3(DATA_PROBLEM_2018_2_311);
        Run_Problem2_3(DATA_PROBLEM_2018_2_312);
        //Run_Problem2_3(DATA_PROBLEM_2018_2_313);

    }
}
