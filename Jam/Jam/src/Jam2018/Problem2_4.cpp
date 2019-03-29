#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
#include <algorithm>
#include <chrono>
using namespace std;

namespace Jam2018
{
#define uint32 unsigned int
    namespace BruteForce
    {
        struct CAS
        {
            int Z;
            int sum;
            CAS(int Z, int sum) :Z(Z), sum(sum) {};
        };

        void CanBuidParks(int R, int C, int** arr, int Z, bool& pass)
        {
            bool existedEmptyBlock = false;
            for (int i = 0; i < R; i++)
            {
                for (int j = 0; j < C; j++)
                {
                    //duyệt những block dùng cho xây dựng công viên
                    if (arr[i][j] > Z)
                    {
                        existedEmptyBlock = true;
                        //kiểm tra xem có block liền kề có trống không
                        //nếu đã tìm đc trường hợp thỏa mãn (pass = true) thì không cần check các trường hợp còn lại
                        if (!pass)
                        {
                            std::vector<int*> childrens;

                            if (i + 1 < R && arr[i + 1][j] > Z)
                            {
                                childrens.push_back(&arr[i + 1][j]);
                            }

                            if (i - 1 >= 0 && arr[i - 1][j] > Z)
                            {
                                childrens.push_back(&arr[i - 1][j]);
                            }

                            if (j + 1 < C && arr[i][j + 1] > Z)
                            {
                                childrens.push_back(&arr[i][j + 1]);
                            }

                            if (j - 1 >= 0 && arr[i][j - 1] > Z)
                            {
                                childrens.push_back(&arr[i][j - 1]);
                            }

                            for (int k = 0; k < childrens.size(); k++)
                            {
                                int old1 = arr[i][j];
                                int old2 = *childrens[k];
                                arr[i][j] = Z;//bỏ qua việc check 2 blocks
                                *childrens[k] = Z;
                                CanBuidParks(R, C, arr, Z, pass);
                                arr[i][j] = old1;
                                *childrens[k] = old2;
                            }
                        }



                    }
                }
            }

            if (!existedEmptyBlock)
            {
                pass = true;
            }
        }
        int Caculate(int R, int C, int D, int W, int** arr)
        {
            int total_blocks = R * C;

            std::map<int, int, std::less<int> >  p_map;
            for (int i = 0; i < R; i++)
            {
                for (int j = 0; j < C; j++)
                {
                    if (p_map.find(arr[i][j]) == p_map.end())
                    {
                        p_map[arr[i][j]] = 1;
                    }
                    else
                    {
                        p_map[arr[i][j]]++;
                    }
                }
            }

            int num_skyscraper = 0;
            std::vector<CAS> cases;
            std::map<int, int>::iterator it;
            for (it = p_map.begin(); it != p_map.end(); it++)
            {
                printf("%d %d \n",it->first,it->second);
                //kiểm tra số block là chẵn
                num_skyscraper += it->second;
                int num_block_parks = total_blocks - num_skyscraper;
                if (num_block_parks % 2 == 0)
                {
                    //printf("Pass %d %d \n",it->first,it->second);
                    //tính cost nếu xây dựng thành công
                    int Z = it->first;
                    int num_parks = num_block_parks / 2;
                    int sum = Z * W + num_parks * D;
                    cases.push_back(CAS(Z, sum));
                }
            }

            if(R*C %2 == 0)cases.push_back(CAS(0, 0.5 * R*C* D));//bổ sung thêm trường hợp toàn bộ block là parks

            std::sort(cases.begin(), cases.end(), [](const CAS& t1, const CAS& t2) -> bool
            {
                return t1.sum < t2.sum;
            }
            );

            for (int i = 0; i< cases.size(); i++)
            {
                printf("Z = %d sum = %d \n",cases[i].Z,cases[i].sum);
                bool pass = false;
                CanBuidParks(R, C, arr, cases[i].Z, pass);
                if (pass)
                {
                    printf("PASS: %d %d \n", cases[i].Z, cases[i].sum);
                    //printf("%d\n", cases[i].sum);
                    return cases[i].sum;
                }
            }
            return 0;

        }
        void Run_Problem2_4(const char* inputPath)
        {
            FILE* file = freopen(inputPath, "r", stdin);
            if (file)
            {
                int R, C, D, W;
                cin >> R >> C >> D >> W;
                printf("%d %d %d %d\n", R, C, D, W);
                int** arr = new int*[R];
                for (int j = 0; j < R; j++)
                {
                    arr[j] = new int[C];
                }

                for (int i = 0; i < R; i++)
                {
                    for (int j = 0; j < C; j++)
                    {
                        cin >> arr[i][j];
                        printf("%d ", arr[i][j]);
                    }
                    printf("\n");
                }

                //TOFO
                auto begin = chrono::high_resolution_clock::now();
                int cost = Caculate(R, C, D, W, arr);
                printf("cost = %d\n",cost);
                auto end = chrono::high_resolution_clock::now();
                auto dur = end - begin;
                auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
                cout << ms << " ms" << endl;
                //fclose (stdin);
            }


        }
    }
	


    void Problem2_4()
    {
        //Run_Problem2_4(DATA_PROBLEM_2018_2_401);
        //Run_Problem2_4(DATA_PROBLEM_2018_2_410);
        //Run_Problem2_4(DATA_PROBLEM_2018_2_411);
        //BruteForce::Run_Problem2_4("D:\\Training\\github\\data\\2018_round2\\D\\sample-2.in");
        BruteForce::Run_Problem2_4("D:\\Training\\github\\data\\2018_round2\\D\\subtask2\\D-data-new-034.in");
        //Run_Problem2_4(DATA_PROBLEM_2018_2_413);

    }
}
