#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include<list>
#include<chrono>
#include <algorithm>
#include <set>
#include <numeric>      // std::iota
using namespace std;
//Complexity : Building TreeMap O(N log N) + Sorting Cabs O(M log M) + Finding passengers O(M log N) = O(M log M + (M + N) log N)
//Lời giải của bàn toán khá đơn giản, tuy nhiên tôi ko thực sự hình dung rõ về tính đúng đắn
//Step1: tạo ra các pair gổm (distance x,số riders), lưu các pair vào BST-Balance cho dễ dàng tìm kiếm sau này
//Step2: Xắp xếp drivers vào 1 mảng theo thứ tự tăng dần cảu endpoint, nếu enpoint bằng nhau thì xếp theo giảm dần của startpoint
//Các dirvers được xắp xếp như trên được định nghĩa tương đương với khả năng tìm thấy khách tăng dần
//Step3: duyệt mảng drivers trên, với mỗi driver tìm riders có distance x lớn hơn và gần nhất với driver.startpoint
//nếu x > driver.endpoint => quyết định matching cặp này => remove rider khỏi tree
namespace Jam2019
{
#define UINT8 unsigned char
#define INT16 short int
#define UINT32 unsigned int
#define INT32  int
#define INT64 long long int
#define UINT64 unsigned long long

#if 1 //FAIL solution: take 12 s
    struct Driver
    {
        int y, z;
        Driver(int y, int z) :y(y), z(z) {};
    };

    void Run_Problem2_5(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);

        UINT32 T;//number of testcase
        UINT32 N; //number of rider
        UINT32 M; //number of driver
        UINT32 x; //expected distance from rider
        UINT32 y, z; //expected distance of driver from y -> z


        auto comp = [](const UINT32& key1, const UINT32& key2) { return key1 < key2; };

        if (fi)
        {
            cin >> T;
            //printf("%d\n",T);

            for (int i = 0; i < T; i++)
            {

                //std::map<UINT32, UINT32, decltype(comp)> riders(comp); //?????????
                //[WARNING] dùng std::map thay cho mutilset nhưng không thành công
                //cần tỉm hiểu vì sao
                std::map<UINT32, UINT32> riders;


                cin >> N;
                cin >> M;

                //printf("%d %d\n", N,M);

                for (int j = 0; j < N; j++)
                {
                    cin >> x;
                    auto it = riders.find(x);
                    if (it == riders.end())
                    {
                        riders[x] = 1;
                    }
                    else
                    {
                        it->second++;
                    }
                    //printf("%d ",x);
                }
                //printf("\n");

                std::vector<Driver*> drivers(M,nullptr);
                for (int j = 0; j < M; j++)
                {
                    cin >> y;
                    cin >> z;
                    //printf("%d %d\n", y,z);
                    drivers[j]  = new Driver(y, z);
                }

                //sort
                std::sort(drivers.begin(), drivers.end(), [](Driver* a, Driver* b)->bool {
                    if (a->z < b->z)
                    {
                        return true;
                    }
                    else if (a->z == b->z)
                    {
                        if (a->y > b->y) return true;
                    }
                    return false;
                }
                );

                UINT32 matching = 0;

                for (int j = 0; j < M; j++)
                {
                    Driver* driver = drivers[j];
                    auto nearest = riders.lower_bound(driver->y);
                    if (nearest != riders.end())
                    {
                        UINT32 distance = nearest->first;
                        if (distance <= driver->z)
                        {
                            matching++;
                            nearest->second--;
                            if (nearest->second == 0)
                            {
                                riders.erase(nearest);
                            }
                        }
                    }
                }

                for (int j = 0; j < M; j++)
                {
                    delete  drivers[j];
                }


                cout << matching << "\n";

            }

            fclose(fi);
        }
    }
#else //good solution take 2.8 s
    int match(int n, int m, vector<int> &x, vector<int> &y, vector<int> &z) {
            multiset<int> ms(x.begin(), x.end());
            vector<int> idx(m);
            iota(idx.begin(), idx.end(), 0);//Store increasing sequence
            sort(idx.begin(), idx.end(), [&](int i, int j) {
                    if (z[i] != z[j])
                            return z[i] < z[j];
                    return y[i] < y[j];
            });
            int ans = 0;
            //O(NlogN)
            for (auto i : idx) {
                    auto it = ms.lower_bound(y[i]);
                    if (it == ms.end() || *it > z[i])
                            continue;
                    ++ans;
                    ms.erase(it);
            }
            return ans;
    }

    void Run_Problem2_5(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);
        if(fi)
        {
            cout.sync_with_stdio(false);
            cin.tie(nullptr);
            int nTests;
            cin >> nTests;
            while (nTests--) {
                    int n, m;
                    cin >> n >> m;
                    vector<int> x(n);
                    for (int i = 0; i < n; ++i)
                            cin >> x[i];
                    vector<int> y(m), z(m);
                    for (int i = 0; i < m; ++i)
                            cin >> y[i] >> z[i];
                    cout << match(n, m, x, y, z) << '\n';
            }
        }

    }
#endif

    void Problem2_5()
    {
        auto begin = chrono::high_resolution_clock::now();
        Run_Problem2_5("D:\\Training\\github\\hello-world\\reference\\Sample\\2019\\round2\\2nd_E\\subtask2\\P3-data-007.in");
        //Run_Problem2_5("D:\\Training\\github\\hello-world\\reference\\Sample\\2019\\round2\\2nd_E\\subtask1\\P3-data-001.in");
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout << "\n\n" << ms << " ms" << endl;//3249 ms
    }
}
