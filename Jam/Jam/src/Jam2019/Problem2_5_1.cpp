#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
#include <vector>
using namespace std;
//Time complexity of the Ford Fulkerson based algorithm is O(V x E)
//https://www.geeksforgeeks.org/maximum-bipartite-matching/
namespace Jam2019
{
#define UINT8 unsigned char
#define INT16 short int
#define UINT32 unsigned int
#define INT32  int
#define INT64 long long int
#define UINT64 unsigned long long 


    struct Rider
    {
        INT32 x;
        std::vector<UINT32> drivers;
        Rider() : x(-1) {};
    };

    bool bpm(Rider* riders , int rider_id,
        bool* seen, int* matchR)
    {
        //get Rider from rider_id
        Rider& rider = riders[rider_id];
        //find all potential drivers of rider
        for (int v = 0; v < rider.drivers.size(); v++)
        {
            //get id of driver
            int driver_id = rider.drivers[v];
            // if this driver was not visited
            if (!seen[driver_id])
            {
                // Mark driver_id as visited 
                seen[driver_id] = true;

                //if currently, driver don't take any rider
                //if driver already took rider => try to find another rider for him
                if (matchR[driver_id] < 0 || bpm(riders, matchR[driver_id],
                    seen, matchR))
                {
                    matchR[driver_id] = rider_id;
                    return true;
                }
            }
        }
        return false;
    }

    // Returns maximum number 
    // of matching from M to N 
    int maxBPM(Rider* riders, const UINT32 num_rider, const UINT32 num_driver)
    {
        int* matchR = new int[num_driver];

        // Initially all jobs are available 
        memset(matchR, -1, sizeof(int) * num_driver);

        // Count of jobs assigned to applicants 
        int result = 0;

        bool* seen = new bool[num_driver];
       
        for (int u = 0; u < num_rider; u++)
        {
            // Mark all jobs as not seen  
            // for next applicant. 
            memset(seen, 0, sizeof(bool)*num_driver);
            // Find if the applicant 'u' can get a job 
            if (bpm(riders, u, seen, matchR))
                result++;

        }
        //delete[] seen;
        //delete[] matchR;

        return result;
    }


    void Run_Problem2_5(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);

        UINT32 T;//number of testcase
        UINT32 N; //number of rider
        UINT32 M; //number of driver
        UINT32 x; //expected distance from rider
        UINT32 y, z; //expected distance of driver from y -> z

        Rider* riders;
        if (fi)
        {
            cin >> T;
            //printf("%d\n",T);
            for (int i = 0; i < T; i++)
            {
                cin >> N;
                cin >> M;
                //printf("%d %d\n", N,M);
                riders = new Rider[N];

                for (int j = 0; j < N; j++)
                {
                    cin >> x;
                    riders[j].x = x;
                    //printf("%d ",x);
                }
                //printf("\n");

                for (int j = 0; j < M; j++)
                {
                    cin >> y;
                    cin >> z;
                    //printf("%d %d\n", y,z);
                    for (int k = 0; k < N; k++)
                    {
                        if (riders[k].x >= y && riders[k].x <= z)
                        {
                            riders[k].drivers.push_back(j);
                            //printf("riders[%d]: %d %d %d\n",k, riders[k].x,y,z);
                        }
                    }
                }

                UINT32 ret = maxBPM(riders,N,M);
                cout << ret << "\n";

                delete[] riders;

            }
            fclose(fi);
        }
    }

    void Problem2_5()
    {
        Run_Problem2_5("D:\\Training\\github\\hello-world\\reference\\Exam\\2019\\round2\\problem5\\input001.txt");
    }
}