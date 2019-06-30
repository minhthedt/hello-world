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

    int Run_Problem2_4_TestCase(UINT32** G, UINT32* S, UINT32 N)
    {
        //find vertices which is potential alliance
        UINT32 sum = 0;//number of 3 - alliance
        for (int i = 0; i < N; i++)
        {
            //if i have more than 2 neighbors (precondition to belong 3-alliance)
            if (S[i] >= 2)
            {
                //find neighbor vertices of i
                std::vector<int> arr;
                for (int j = 0; j < N; j++)
                {
                    if (G[i][j] == 1)
                    {
                        arr.push_back(j); 
                    }
                }
                std::vector<int> arr_back = arr;
                while (arr.size() > 0)
                {
                    int p = arr.back();//get last element
                    for (int k = 0; k < arr.size() - 1; k++)
                    {
                        if (G[p][arr[k]] == 1)
                        {
                            sum++;
                        }
                    }

                    arr.pop_back();
                }

                //we already find all 3-alliance which contain i vertices
                //we need to remove i from G
                for (int m = 0; m < arr_back.size(); m++)
                {
                    //substract 1 will all neighbors of i
                    S[arr_back[m]] -= 1;
                }
                //remove i so we need to update G
                for (int j = 0; j < N; j++)
                {
                    G[i][j] = 0;
                    G[j][i] = 0;
                }
            }
        }

        //printf("3-alliances = %d\n",sum);
        return sum;
    }

    void Run_Problem2_4(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);
        UINT32 T; //number of test case
        UINT32 N; //3 ≤ N ≤ 5,000
        UINT32 M; //1 ≤ M ≤ min(1, 000, 000, N ×(N - 1) / 2) - number of pair of alliances
        UINT32 x, y; //1 ≤ x < y ≤ N - numbers of tribes
        UINT32** G;//adjacent matrix G[N][N]
        UINT32** G_BAK;//matrix G1[N][N] - using for backup
        UINT32* S;//S[i] count adject edge of vertice i
        UINT32* S_BAK;
        if (fi)
        {
            cin >> T;
            //printf("%d \n",T);
            for (int i = 0; i < T; i++)
            {
                cin >> N;
                cin >> M;
                //printf("%d %d\n",N,M);
                S = new UINT32[N];
                S_BAK = new UINT32[N];
                memset(S, 0, sizeof(UINT32)*N);
                memset(S_BAK, 0, sizeof(UINT32)*N);
                G = new UINT32*[N];
                G_BAK = new UINT32*[N];
                for (int g = 0; g < N; g++)
                {
                    G[g] = new UINT32[N];
                    G_BAK[g] = new UINT32[N];
                    memset(G[g],0,sizeof(UINT32)*N);
                    memset(G_BAK[g], 0, sizeof(UINT32)*N);
                }
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
                int sum1 = Run_Problem2_4_TestCase(G_alliance, S_alliance,N);

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

                int sum2 = Run_Problem2_4_TestCase(G_hostility, S_hostility, N);

                cout << sum1 + sum2 << std::endl;
                //releae memory
                for (int g = 0; g > N; g++)
                {
                    delete[] G[g];
                    delete[] G_BAK[g];
                }
                delete[] G;
                delete[] G_BAK;
                delete[] S;
                delete[] S_BAK;
            }
            fclose(fi);
        }
    }

    void Problem2_4()
    {
        Run_Problem2_4("D:\\Training\\github\\hello-world\\reference\\Exam\\2019\\round2\\problem4\\input001.txt");
    }
}