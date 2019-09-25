#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <chrono>
using namespace std;

namespace Final2018
{
#define UINT8 unsigned char
#define INT16 short int
#define UINT32 unsigned int
#define INT32  int
#define INT64 signed long long
#define UINT64 unsigned long long
#define MODULO  1000000007

    void problem1(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);

        int a[6];
        if (fi)
        {
            int count = 0;
            int modul = 0;
            for (int i = 1; i <= 5; i++)
            {
                cin >> a[i];
                //printf("%d ",a[i]);
            }

            //a[5]
            //bao gom phan tu (5)
            int n5 = a[5];
            a[5] = 0;
            //bao gom phan tu (4)(4,1)
            int n4 = 0;
            for (int i = 1; i <= a[4]; i++)
            {
                if (a[1] > 0)
                {
                    a[1]--;
                }
                n4++;
            }
            a[4] = 0;
            //bao gom (3 2) (3 1 1 )
            int n3 = 0;
            for (int i = 1; i <= a[3]; i++)
            {
                if (a[2] > 0)
                {
                    a[2]--;
                }
                else if (a[1] > 0)
                {
                    if(a[1] >= 2) a[1] -= 2;
                    else if(a[1] >= 1) a[1] -= 1;
                }
                n3++;
               
            }
            a[3] = 0;
            //bao gom (2 2) (2 2 1)  (2 1 1 1)
            a[4] = a[2]*2 / 4;
            a[2] = a[2] % 2;
            for (int i = 1; i <= a[4]; i++)
            {
                if (a[1] > 0)
                {
                    a[1]--;
                }
                n4++;
            }
            a[4] = 0;

            int n2 = 0;
            for (int i = 1; i <= a[2]; i++)
            {
                if (a[1] > 0)
                {
                    if(a[1] >= 3) a[1] -= 3; 
                    else if (a[1] >= 2) a[1] -= 2;
                    else if (a[1] >= 1) a[1] -= 1;
                }
                n2++;
            }
            a[2] = 0;

            int n1 = 0;
            n1 = a[1] / 5;
            if (a[1] % 5 != 0) n1++;

            int sum = n1 + n2 + n3 + n4 + n5;
            printf("%d", sum);

        }
        else
        {
            printf("FAIL open %s\n", inputPath);
        }
    };

    void Run_problem1()
    {
        auto begin = chrono::high_resolution_clock::now();
        problem1("D:\\Training\\github\\hello-world\\reference\\Sample\\\Final\\2018\\A\\data-4.in");
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout << "\n\n" << ms << " ms" << endl;//2 ms
    }


    void problem2(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);
        int N, M;
        int* values = nullptr;
        if (fi)
        {
            cin >> N >> M;
            //printf("%d %d\n",N,M);
            std::vector<int> arr1;
            std::vector<int> arr2;
            int temp;
            for (int i = 0; i < N; i++)
            {
                cin >> temp;
                if (temp % 10 == 0) arr1.push_back(temp);
                else arr2.push_back(temp);
                //printf("%d ", values[i]);
            }

            std::sort(arr1.begin(), arr1.end(), [](int a, int b)->bool
            {
                return a < b;
            });

            std::sort(arr2.begin(), arr2.end(), [](int a, int b)->bool
            {
                return a > b;
            });
            
            int num_cut = 0;
            int rollcakes = 0;
            for (int i = 0; i < arr1.size(); i++)
            {
                int cut = arr1[i] / 10 - 1;

                if (num_cut + cut < M)
                {
                    rollcakes += cut + 1;
                    num_cut += cut;
                }
                else if (num_cut + cut == M)
                {
                    rollcakes += cut + 1;
                    num_cut += cut;
                    break;
                }
                else
                {
                    cut = M - num_cut;
                    rollcakes += cut;
                    num_cut += cut;
                }
            }

            if (num_cut < M)
            {
                for (int j = 0; j < arr2.size(); j++)
                {
                    int cut = arr2[j] / 10;
                    if (num_cut + cut < M)
                    {
                        rollcakes += cut;
                        num_cut += cut;
                    }
                    else if (num_cut + cut == M)
                    {
                        rollcakes += cut;
                        num_cut += cut;
                        break;
                    }
                    else
                    {
                        rollcakes += M - num_cut;
                        num_cut = M;
                        break;
                    }
                }
            }

            printf("%d", rollcakes);
        }
        else
        {
            printf("FAIL open %s\n", inputPath);
        }
    }

    void Run_problem2()
    {
        auto begin = chrono::high_resolution_clock::now();
        problem2("D:\\Training\\github\\hello-world\\reference\\Sample\\\Final\\2018\\B\\cf-12.in");
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout << "\n\n" << ms << " ms" << endl;//2 ms
    }

    void problem3(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);

        int N;

        if (fi)
        {
            cin >> N;//1 <= N <= 10000; 2 <= Ai <= 100000
            //printf("%d\n",N);
            std::vector<int> A(N,0);
            for (int i = 0; i < N; i++)
            {
                cin >> A[i];
                //printf("%d ", A[i]);
            }

            std::sort(A.begin(), A.end(), [](int a, int b) -> bool
            {
                return a > b;
            });

            UINT64 previous = 0;
            int i;
            UINT64 total_area = 0;
            for (i = 0; i < N; i++)
            {
                if (i + 1 < N && abs(A[i] - A[i + 1]) <= 1)
                {
                    UINT64 current = min(A[i], A[i + 1]);
                    if (previous > 0)
                    {
                        total_area += current * previous;
                        previous = 0;
                        
                    }
                    else
                    {
                        previous = current;
                    }
                    i = i + 1;
                }
            }

            printf("\ntotal = %llu\n", total_area);
        }
        else
        {
            printf("FAIL open %s\n", inputPath);
        }
    }

    void Run_problem3()
    {
        auto begin = chrono::high_resolution_clock::now();
        problem3("D:\\Training\\github\\hello-world\\reference\\Sample\\\Final\\2018\\C\\data-1.in");
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout << "\n\n" << ms << " ms" << endl;//2 ms
    }



    void problem4(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);


        int N;

        if (fi)
        {
            cin >> N;//number student
            //printf("%d\n", N);
            int* X = new int[N];
            set<int> set;
            auto comp = [](const int& a, const int& b) { return a  < b; };
            std::map<int, std::pair<int,int>, decltype(comp) > map(comp);//(X[i], <X[i],number of X[i]>)
            for (int i = 0; i < N; i++)
            {
                cin >> X[i];
                //printf("%d ", X[i]);
                if (map.find(X[i]) == map.end())
                {
                    map[X[i]] = std::pair<int, int>(X[i], 1);
                }
                else
                {
                    map[X[i]].second++;
                }
            }

            int group = 0;
            int pre_student = 0;
            int pre_student_group = 0;
            int cur_student_group = 0;
            int cur_student = 0;
            //printf("size = %d\n",map.size());
            for (auto it = map.begin(); it != map.end(); it++)
            {
                //printf("%d - %d\n", it->second.first, it->second.second);
                cur_student_group = it->second.first;//contion: max student/1 group
                cur_student = it->second.second;//number of students 

                //tim cach tao nhom tu pre_student
                if (pre_student > 0)
                {
                    if (cur_student + pre_student >= pre_student_group)
                    {
                        //tao 1 nhom moi 
                        group++;
                        cur_student -= (pre_student_group - pre_student);

                        //tao nhom chi toan cur_student
                        int newadd= cur_student / cur_student_group;
                        group += newadd;
                        //con thua
                        pre_student = cur_student % cur_student_group;
                        if(cur_student != 0)  pre_student_group = cur_student_group;
                    }
                    else
                    {
                        //chua the tao nhom moi
                        pre_student += cur_student;
                        //giu nguyen pre_student_group
                    }
                }
                else
                {
                    group += cur_student / cur_student_group;

                    pre_student = cur_student % cur_student_group;
                    pre_student_group = cur_student_group;
                }

            }
            if (pre_student != 0) group++;
            printf("%d \n", group);
        }
        else
        {
            printf("FAIL open %s\n", inputPath);
        }
    }

    void Run_problem4()
    {
        auto begin = chrono::high_resolution_clock::now();
        problem4("D:\\Training\\github\\hello-world\\reference\\Sample\\\Final\\2018\\D\\P5-data-029-4.in");
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout << "\n\n" << ms << " ms" << endl;//2 ms
    }


    void problem5(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);
        if (fi)
        {

        }
        else
        {
            printf("FAIL open %s\n", inputPath);
        }
    }

    void Run_problem5()
    {
        auto begin = chrono::high_resolution_clock::now();
        problem5("D:\\Training\\github\\hello-world\\reference\\Sample\\\Final\\2018\\E\\P5-data-029-4.in");
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout << "\n\n" << ms << " ms" << endl;//2 ms
    }

    void problem6(const char* inputPath)
    {
        
        FILE* fi = freopen(inputPath, "r", stdin);
        if (fi)
        {
            UINT64 R, C, K;
            UINT64 ret = 1;
            UINT64 max_tile = 0;
            //1 ≤ R ≤ 1 000 000 ; 2 ≤ C ≤ 1; 000; 000; 000 ,  0 ≤ K ≤ 1; 000.  
            int r, c;
            cin >> R >> C >> K;
            //printf("%d %d %d\n",R,C,K);
            std::map<int, std::vector<int>> data;
            for (int i = 0; i < K; i++)
            {
                cin >> r >> c;
                //printf("%d %d\n",r,c);
                data[r].push_back(c);
            }

            for (auto it = data.begin(); it != data.end(); it++)
            {
                std::vector<int>& val= it->second;
                std::sort(val.begin(), val.end(), [](int a, int b)->bool
                {
                    return a < b;
                });

                int num = val.size();
                //from val[0] -> val[num]
                for (int j = 1; j < num; j++)
                {
                    int space = val[j] - val[j - 1] - 1;
                    if (space % 2 != 0)
                    {
                        ret *= (space / 2 + 1);
                        ret %= MODULO;
                    }
                    max_tile += space / 2;
                }

                //from  1 - > val[0]
                {
                    int space = val[0] - 1;
                    if (space % 2 != 0)
                    {
                        ret *= (space / 2 + 1);
                        ret %= MODULO;
                    }
                    max_tile += space / 2;
                }

                //from val[num-1] -> C;
                {
                    int space = C - val[num - 1];
                    if (space % 2 != 0)
                    {
                        ret *= (space / 2 + 1);
                        ret %= MODULO;
                    }
                    max_tile += space / 2;
                }
               
            }

            //count all row which is empty
            int emptyrow = R - data.size();
            max_tile += emptyrow * (C / 2);
            if (C % 2 == 1)
            {
                ret *= (C / 2 + 1);
                ret %= MODULO;
            }


            printf("%lld %lld \n", max_tile,ret);
        }
        else
        {
            printf("FAIL open %s\n", inputPath);
        }
    }

    void Run_problem6()
    {
        auto begin = chrono::high_resolution_clock::now();
        problem6("D:\\Training\\github\\hello-world\\reference\\Sample\\\Final\\2018\\F\\P6-data-030-8.in");
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout << "\n\n" << ms << " ms" << endl;//2 ms
    }

    void problem7(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);
        if (fi)
        {
            //2 <= N <= 1000
            //1 <= M <= N*(N-1)/2
            //1 <= K <= 100
            int M, N, K;
            int x, y;
            int** graph;
            cin >> N >> M >> K;
            printf("%d %d %d\n", N,M,K);
            graph = new int*[N];
            for (int i = 0; i < N; i++)
            {
                graph[i] = new int[N];
                memset(graph[i],0,N*sizeof(int));
            }

            for (int i = 1; i <= M; i++)
            {
                cin >> x >> y;
                printf("%d %d\n",x,y);
                graph[x - 1][y - 1] = i;
                graph[y - 1][x - 1] = i;
                printf("graph[%d][%d] = %d\n", x-1, y-1,i);
            }

            //BFS de check full connected
            queue<int> q;
            q.push(0);
            bool* visited = new bool[N];
            memset(visited, 0, N);
            visited[0] = true;
            while (!q.empty()) {
                //time lien ke voi dinh 0
                int t = q.front();
                q.pop();
                
                for (int i = 0; i < N; i++)
                {
                    if (!visited[i] && graph[t][i] > 0)
                    {
                        visited[i] = true;
                        q.push(i);
                    }
                }
            }

            for (int i = 0; i < N; i++)
            {
                if (visited[i] == false)
                {
                    printf("not connected !\n");
                }
            }
        }
        else
        {
            printf("FAIL open %s\n", inputPath);
        }
    }

    void Run_problem7()
    {
        auto begin = chrono::high_resolution_clock::now();
        problem7("D:\\Training\\github\\hello-world\\reference\\Sample\\\Final\\2018\\G\\P7-data-001-00.in");
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout << "\n\n" << ms << " ms" << endl;//2 ms
    }
}