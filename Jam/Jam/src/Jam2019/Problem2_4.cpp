#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
#include <vector>
using namespace std;

namespace Jam2019
{
#define UINT8 unsigned char
#define INT16 short int
#define UINT32 unsigned int
#define INT32  int
#define INT64 long long int
#define UINT64 unsigned long long 
#define MAX_N 5000

    int Run_Problem2_4_TestCase(UINT32* ARR, UINT8** G, UINT32* S, UINT32 N)
    {
        //find vertices which is potential alliance
        UINT32 sum = 0;//number of 3 - alliance
        for (int i = 0; i < N; i++)
        {
            //if i have more than 2 neighbors (precondition to belong 3-alliance)
            if (S[i] >= 2)
            {
                //find neighbor vertices of i
                //std::vector<int> arr;
                int size = S[i];//number of neighbor
                
                int temp = 0;
                for (int j = 0; j < N; j++)
                {
                    if (G[i][j] == 1)
                    {
                        //arr.push_back(j); 
                        ARR[temp] = j;
                        temp++;
                        //to remove i so we need to update G
                        G[i][j] = 0;
                        G[j][i] = 0;
                        //substract 1 will all neighbors of i
                        S[j] -= 1;
                    }
                }
                //std::vector<int> arr_back = arr;
                temp = size -1;
                while (temp >= 0)
                {
                    int p = ARR[temp];//get last element
                    for (int k = 0; k < temp; k++)
                    {
                        if (G[p][ARR[k]] == 1)
                        {
                            sum++;
                        }
                    }
                    temp--;
                }

                //we already find all 3-alliance which contain i vertices
                //we need to remove i from G
                //for (int m = 0; m < size; m++)
                //{
                //    //substract 1 will all neighbors of i
                //    S[ARR[m]] -= 1;
                //}
                //remove i so we need to update G
                //for (int j = 0; j < N; j++)
                //{
                //    G[i][j] = 0;
                //    G[j][i] = 0;
                //}
            }
        }

        //printf("3-alliances = %d\n",sum);
        return sum;
    }
#define MY_FIX 1
    void Run_Problem2_4(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);
        UINT32 T; //number of test case
        UINT32 N; //3 ≤ N ≤ 5,000
        UINT32 M; //1 ≤ M ≤ min(1, 000, 000, N ×(N - 1) / 2) - number of pair of alliances
        UINT32 x, y; //1 ≤ x < y ≤ N - numbers of tribes
#if MY_FIX
        UINT8** G;;//adjacent matrix G[N][N]
        UINT8** G_BAK;;//matrix G1[N][N] - using for backup
        UINT32* S;//S[i] count adject edge of vertice i
        UINT32* S_BAK;// = new UINT32[MAX_N];
        UINT32* ARR;

#else
        UINT32** G= new UINT32*[MAX_N]; ;//adjacent matrix G[N][N]
        UINT32** G_BAK = new UINT32*[MAX_N];;//matrix G1[N][N] - using for backup
        UINT32* S = new UINT32[MAX_N];//S[i] count adject edge of vertice i
        UINT32* S_BAK = new UINT32[MAX_N];
        int* ARR = new int[MAX_N];

        memset(ARR, 0, sizeof(int)*MAX_N);
        for (int g = 0; g < MAX_N; g++)
        {
            G[g] = new UINT32[MAX_N];
            G_BAK[g] = new UINT32[MAX_N];
        }
#endif
        if (fi)
        {
            cin >> T;
            //printf("%d \n",T);
            for (int i = 0; i < T; i++)
            {
                cin >> N;
                cin >> M;
                //printf("%d %d\n",N,M);
#if MY_FIX
                ARR = new UINT32[N];
                S = new UINT32[N];
                S_BAK = new UINT32[N];
                memset(S, 0, sizeof(UINT32)*N);
                memset(S_BAK, 0, sizeof(UINT32)*N);
                G = new UINT8*[N];
                G_BAK = new UINT8*[N];
                for (int g = 0; g < N; g++)
                {
                    G[g] = new UINT8[N];
                    G_BAK[g] = new UINT8[N];
                    memset(G[g],0,sizeof(UINT8)*N);
                    memset(G_BAK[g], 0, sizeof(UINT8)*N);
                }
#else
                memset(S, 0, sizeof(UINT32)*N);
                memset(S_BAK, 0, sizeof(UINT32)*N);
                for (int g = 0; g < N; g++)
                {
                    memset(G[g], 0, sizeof(UINT32)*N);
                    memset(G_BAK[g], 0, sizeof(UINT32)*N);
                }
#endif
                for (int j = 0; j < M; j++)
                {
                    cin >> x;
                    cin >> y;
                    //printf("%d %d \n", x, y);
                    G[x-1][y-1] = 1;
                    G[y - 1][x - 1] = 1;
                    G_BAK[x - 1][y - 1] = 1;
                    G_BAK[y - 1][x - 1] = 1;
                    S[x - 1] += 1;
                    S[y - 1] += 1;
                    S_BAK[x - 1] += 1;
                    S_BAK[y - 1] += 1;
                }

                //Handle
                auto G_alliance = G;
                auto S_alliance = S;
                int sum1 = Run_Problem2_4_TestCase(ARR,G_alliance, S_alliance,N);

                auto G_hostility = G;
                auto S_hostility = S;
                //calculate again
                for (int j = 0; j < N; j++)
                {
                    S_hostility[j] = N - S_BAK[j] - 1;
                }

                for (int j = 0; j < N; j++)
                {
                    for (int k = 0; k < N; k++)
                    {
                        if (j == k)
                        {
                            G_hostility[j][k] = 0;
                        }
                        else
                        {
                            if (G_BAK[j][k] == 1) G_hostility[j][k] = 0;
                            else G_hostility[j][k] = 1;
                        }
                    }
                }

                int sum2 = Run_Problem2_4_TestCase(ARR,G_hostility, S_hostility, N);

                cout << sum1 + sum2 << std::endl;

                //releae memory
#if MY_FIX
                for (int g = 0; g < N; g++)
                {
                    delete[] G[g];
                    delete[] G_BAK[g];
                }
                delete[] G;
                delete[] G_BAK;
                delete[] S;
                delete[] S_BAK;
                delete[] ARR;
#endif
            }
#if !MY_FIX
            for (int g = 0; g < MAX_N; g++)
            {
                delete[] G[g];
                delete[] G_BAK[g];
            }
            delete[] G;
            delete[] G_BAK;
            delete[] S;
            delete[] S_BAK;
            delete[] ARR;
#endif
           

            fclose(fi);
        }
    }

    void Problem2_4()
    {
        Run_Problem2_4("D:\\Training\\github\\hello-world\\reference\\Exam\\2019\\round2\\problem4\\input001.txt");
    }
}