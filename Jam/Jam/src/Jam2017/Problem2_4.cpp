#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
#include <vector>
using namespace std;

namespace Jam2017
{
    #define uint32 unsigned long long
    #define int32  signed long long
    extern void GetFilePaths(const std::string&  path,std::vector<std::string>& output,std::vector<std::string> ext = std::vector<std::string>());
    extern std::vector<int32> GetResult(const char* path,int num);

    struct Tree
    {
        uint32 x,y1,y2;
        Tree():x(0),y1(0),y2(0){};
        Tree(uint32 _x, uint32 _y1, uint32 _y2):
            x(_x),
            y1(_y1),
            y2(_y2)
        {};

    };

    struct TestCase
    {
        uint32 N;
        Tree* trees;
        TestCase(): N(0),trees(nullptr) {};
        ~TestCase(){delete[] trees;};

    };

    bool canJump(const MMath::Point& A,const MMath::Point& B,const MMath::Point& C,const MMath::Point&D)
    {
        MMath::Line line1(A,B);
        MMath::Line line2(C,D);
        return line1.Intersect(line2);
    }

    void BruteforceSpiderJump(const TestCase& tc, int from,int& count)
    {
        if(from == tc.N-1)
        {
            count++;
            return;
        }

        for(int i = from +1 ; i < tc.N; i++)
        {

             MMath::Point fromTop(tc.trees[from].x,tc.trees[from].y2);
             MMath::Point fromBottom(tc.trees[from].x,tc.trees[from].y1);
             MMath::Point toTop(tc.trees[i].x,tc.trees[i].y2);
             MMath::Point toBottom(tc.trees[i].x,tc.trees[i].y1);
             if(i == from +1)
             {
                 for(int j =0; j < 4; j++)
                 {
                     //2 tree liền nhau thì đương nhiên nhảy đc
                     BruteforceSpiderJump(tc,i,count);
                 }
             }else
             {
                 //duyet qua cac tree giua xem có thỏa mãn để nhảy không
                 bool pass = true;
                 for(int j = from +1; j < i; j++)
                 {
                     MMath::Point TreeTop(tc.trees[j].x,tc.trees[j].y2);
                     MMath::Point TreeBottom(tc.trees[j].x,tc.trees[j].y1);
                     bool jump = false;
                     if(canJump(fromTop,toTop,TreeTop,TreeBottom))
                     {
                         jump =  true;
                         BruteforceSpiderJump(tc,j,count);
                     }

                     if(canJump(fromTop,toBottom,TreeTop,TreeBottom))
                     {
                         jump =  true;
                         BruteforceSpiderJump(tc,j,count);
                     }

                     if(canJump(fromBottom,toTop,TreeTop,TreeBottom))
                     {
                         jump =  true;
                         BruteforceSpiderJump(tc,j,count);
                     }

                     if(canJump(fromBottom,toBottom,TreeTop,TreeBottom))
                     {
                         jump =  true;
                         BruteforceSpiderJump(tc,j,count);
                     }

                     if(jump == false)
                     {
                         pass = false;
                         //không cần check tree tiếp theo
                         break;
                     }
                 }

                 //không cần nhảy đến tree tiếp theo
                 if(!pass)
                 {
                     break;
                 }else
                 {
                    BruteforceSpiderJump(tc,i,count);
                 }
             }

        }
    }

    uint32 RunTestCase2_4(const TestCase& tc)
    {
        int count = 0;
        BruteforceSpiderJump(tc,0,count);
        return count;
    }
    void Run_Problem2_4(const char* inputPath)
    {
         uint32 T,N;
         int32 x,y1,y2;
         TestCase* tcs = nullptr;
         std::vector<int32> out;
         FILE* fi = freopen(inputPath, "r",stdin);
         if(fi)
         {
            cin >> T;
            tcs = new TestCase[T];
            printf("%llu\n",T);
            for(int i =0; i < T; i++)
            {
                cin >> N;
                tcs[i].N = N;
                tcs[i].trees = new Tree[N];
                printf("%llu\n",N);
                for(int j =0; j < N; j++)
                {
                    cin >> x;
                    cin >> y1;
                    cin >> y2;
                    printf("%lld %lld %lld\n",x,y1,y2);
                     tcs[i].trees[j].x = x;
                     tcs[i].trees[j].y1 = y1;
                     tcs[i].trees[j].y2 = y2;
                }

                 out.push_back(RunTestCase2_4(tcs[i]));
            }


         }
        fclose(fi);

        std::string outpath = inputPath;
        outpath = outpath.replace(outpath.length()-12,5,"output");
        std::vector<int32> result = GetResult(outpath.c_str(),T);
        bool pass = true;
        for(int i =0; i < T;i++)
        {
            printf("%lld ----> %lld\n",out[i],result[i]);
            if(out[i] != result[i])
            {
                pass = false;
                break;
            }
        }

//        printf("%s \n",pass ? "PASS" : "FAIL");
//
//        MMath::Point A(0,1);
//        MMath::Point B(2,0);
//        MMath::Point C(0,0);
//        MMath::Point D(1.5,0.5);
//        MMath::Line line1(A,B);
//        MMath::Line line2(C,D);
//
//        printf("%s \n",line1.Intersect(line2) ? "intersect" : "NO intersect");
    }


    void Problem2_4()
    {
        //Run_Problem2_4(DATA_PROBLEM_2018_2_401);
        //Run_Problem2_4(DATA_PROBLEM_2018_2_410);
        //Run_Problem2_4(DATA_PROBLEM_2018_2_411);
        Run_Problem2_4("D:\\Training\\github\\hello-world\\reference\\Exam\\2017\\sample\\Round2_Problem4_set1\\input006.txt");
        //Run_Problem2_4(DATA_PROBLEM_2018_2_413);

    }
}
