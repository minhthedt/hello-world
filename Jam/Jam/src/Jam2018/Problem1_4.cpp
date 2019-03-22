#include "Common.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include<iostream>
#include <algorithm>
using namespace std;

namespace Jam2018
{
#define MAX_SUM  20000000
    extern void split(const std::string &s, char delim, std::vector<std::string> &elems);
    extern std::vector<std::string> split(const std::string &s, char delim);

    struct Vertice
    {
        int A, B, C, T;
        bool isValid;
        Vertice():isValid(false)
        {
        };

        void set(int a, int b, int c, int t)
        {
            isValid = true;
            this->A = a;
            this->B = b;
            this->C = c;
            this->T = t;
        }
        unsigned int cost(int num)
        {
            if (!isValid) return MAX_SUM;
            if (num <= T) return 0;
            return C * (num - T) * (num - T);
        }
    };

    bool checkPass(int N, int M, int K, Vertice** G, int particiants)
    {
        int i;
        unsigned int* Len = new unsigned int[N];//chua khoang cach cua N dinh
        int* S = new int[N];// check trang thai xem dinh nay xet chua
        int* P = new int[N];// chua dinh truoc do
        int a = 1;
        int b = N;
        a--;
        b--;

        for (int i = 0; i < N; i++)
        {
            Len[i] = MAX_SUM;//infinity
            S[i] = 0;
            P[i] = a; //diem bat dau
        }

        Len[a] = 0; //a -> a


        while (S[b] == 0)
        {
            for (i = 0; i < N; i++)
            {
                if (!S[i] && Len[i] != -1) //tim diem chua xet va len != -1
                    break;
            }

            if (i >= N)
            {
                printf("dont dijkstra\n");
                break;
            }

            for (int j = 0; j < N; j++)
            {
                if (!S[j] && Len[i] > Len[j])
                {
                    i = j;
                }
            }

            S[i] = 1;                       // cho i vao danh sach xet roi

            for (int j = 0; j < N; j++)
            {
                if (!S[j])
                {
                    unsigned int cost = G[i][j].cost(particiants);
                    //printf("%d -> %d = cost = %d \n",i,j, cost);
                    if (Len[i] + cost < Len[j]) {
                        Len[j] = Len[i] + cost;      // thay doi len
                        P[j] = i;                       // danh dau diem truoc no
                    }
                }

            }
        }

        //printf("done dijkstra\n");

        ///* Do ta dang tinh toan tu dinh 0 nen
        //muon hien thi tu dinh 1 thi can dung i + 1 de phu hop */

        //printf("start find path\n");

        //if (Len[b] >= 0 && Len[b] != -1) {
        //    printf("Length of %d to %d is %d\n", a + 1, b + 1, Len[b]);

        //    // truy vet (i luc nay = b)
        //    while (i != a) {
        //        printf("%d <-- ", i + 1);
        //        i = P[i];
        //    }
        //    printf("%d", a + 1);
        //}
        //else {
        //    printf("khong co duong di tu %d den %d\n", a + 1, b + 1);
        //}

        //printf("\ndone find path\n");

        bool pass = false;
        if (Len[b] <= K)   { pass = true; }
        delete[] Len;
        delete[] S;
        delete[] P;
        return pass;
    }

    void Run_Problem1_4(const char* inputPath)
    {
        printf("Problem 4: %s\n", inputPath);
        auto begin = chrono::high_resolution_clock::now();

        int minC = 0;
        int maxT = 0;
        int N, M, K;
        int currentLine = 0;
        Vertice** G = nullptr;
        stringstream stream;
        std::string line;
        ifstream myfile(inputPath);

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
                    if (words.size() == 3)
                    {
                        N = atoi(words[0].c_str());
                        M = atoi(words[1].c_str());
                        K = atoi(words[2].c_str());

                        G = new Vertice*[N];
                        for (int i = 0; i < N; i++)
                        {
                            G[i] = new Vertice[N];
                        }
                    }
                    else
                    {
                        printf("Error input line 1");
                    }
                }
                else
                {
                    std::vector<std::string> words = split(line, ' ');
                    if (words.size() == 4)
                    {
                        int A = atoi(words[0].c_str());
                        int B = atoi(words[1].c_str());
                        int C = atoi(words[2].c_str());
                        int TT = atoi(words[3].c_str());

                        if (minC == 0 || minC > C) minC = C;
                        if (maxT < TT) maxT = TT;
                        //luu vao matrix
                        G[A - 1][B - 1].set(A,B,C,TT);
                        if (currentLine - 1 == M) break;
                    }
                    else
                    {
                        printf("Error input line %d \n", currentLine);
                    }
                }

                

            }
            myfile.close();
        }

        //checkPass(N, M, K, G, 10);
        int max_participants = std::sqrt(K/(minC*minC)) + maxT;
        int min_participants = 0;
        while (min_participants < max_participants - 1)
        {
            int number = (max_participants + min_participants) / 2;
            if (!checkPass(N, M, K, G, number))
            {
                max_participants = number;
            }
            else
            {
                min_participants = number;
            }
        }

        int num = min_participants;
 /*       for (int k = 1; k < max_participants; k++)
        {
            if (!checkPass(N, M, K, G, k))
            {
                num = k - 1;
                break;
            }
        }*/

        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        std::cout << ms << " ms" << endl;

        printf("find num = %d\n",num);

    }

    void Problem1_4()
    {
        Run_Problem1_4(DATA_PROBLEM_2018_1_401);
        Run_Problem1_4(DATA_PROBLEM_2018_1_410);
        Run_Problem1_4(DATA_PROBLEM_2018_1_411);
        Run_Problem1_4(DATA_PROBLEM_2018_1_412);
        Run_Problem1_4(DATA_PROBLEM_2018_1_413);

    }
}
