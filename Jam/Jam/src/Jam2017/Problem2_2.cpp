#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
#include <chrono>
#include <array>
using namespace std;

namespace Jam2017
{
    #define int32 signed long long
    #define uint32 unsigned long long

    extern void GetFilePaths(const std::string&  path,std::vector<std::string>& output,std::vector<std::string> ext = std::vector<std::string>());

    struct TestCase
    {
        int N;
        std::vector<std::array<int,2>> points;
        TestCase():N(0){};
    };

    std::vector<int32> GetResult(const char* path,int num)
    {
        std::vector<int32> result;
        FILE *fi = fopen(path, "r");
        if(!fi)
        {
            printf("ERROR : %s",path);
            return result;
        }
        for(int i =0; i < num;i++)
        {
            uint32 out;
            fscanf(fi, "%llu", &out);
            result.push_back(out);
        }
        fclose(fi);

        return result;
    }
    //Greedy Algorithm ?? Không hiểu lời giải nên ko implement
    //Brute Force
    uint32 RunTestCase(const TestCase& tc)
    {
        //double thiness = 1;
        //uint32 ii;
        //uint32 jj;
        uint32 perimeter = 0;
        //for(uint32 i =0; i < tc.N - 1;i++)
        //{
        //    for(uint32 j = i+1; j < tc.N;j++)
        //    {
        //        auto& point1 = tc.points[i];
        //        auto& point2 = tc.points[j];
        //        uint32 width = abs(point1[0] - point2[0]);
        //        uint32 heigh = abs(point1[1] - point2[1]);
        //        //printf("width = %lld heigh = %lld\n",width,heigh);
        //        if(width < heigh)
        //        {
        //            if(thiness >= (double)width/heigh)
        //            {
        //                thiness = (double)width/heigh;
        //                ii = i;
        //                jj = j;
        //                perimeter = 2 * (width + heigh);
        //            }

        //        }
        //        else
        //        {
        //            if(thiness >= (double)heigh/width)
        //            {
        //                thiness = (double)heigh/width;
        //                ii = i;
        //                jj = j;
        //                perimeter = 2 * (width + heigh);
        //            }
        //       }
        //    }
        //}
        //printf("perimeter = %lld\n",perimeter);
        return perimeter;
    }

    void Run_Problem2_2(const char* inputPath)
    {
        uint32 T,N;//T = number of test case, N is number of points in one test case
        int32 a,b; //a,b is coordinate of each point
        FILE* file = freopen(inputPath, "r", stdin);
        TestCase* tests = nullptr;
        std::vector<int32> out;
        if(file)
        {
            cin >> T;
            //printf("%lld\n",T);
            tests =  new TestCase[T];
            for(int i =0 ; i < T;i++)
            {
                cin >> N;
                //printf("%lld\n",N);
                tests[i].N = N;
                for(int j =0; j < N; j++)
                {
                    cin >> a;
                    cin >> b;
                    //printf("%lld %lld\n",a,b);
                    //tests[i].points.push_back(std::array<int,2>{a,b});
                }
                out.push_back(RunTestCase(tests[i]));
            }
        }

        std::string outpath = inputPath;
        outpath = outpath.substr(0,outpath.length()-3);
        outpath += ".out";
        std::vector<int32> result = GetResult(outpath.c_str(),T);
        bool pass = true;
        for(int i =0; i < T;i++)
        {
            //printf("%lld ----> %lld\n",out[i],result[i]);
            if(out[i] != result[i])
            {
                pass = false;
                break;
            }
        }
        printf("%s \n",pass ? "PASS" : "FAIL");
    }

    void Problem2_2()
    {
        auto begin = chrono::high_resolution_clock::now();

        Run_Problem2_2("D:\\Training\\github\\hello-world\\reference\\Exam\\2017\\sample\\Round2_Problem2_Set1\\002.in");

        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout <<"\n"<< ms << " ms" << endl;//2 ms
    }
}
