#include "Common.h"
#include <iostream>
#include <math.h>       /* round, floor, ceil, trunc */

using namespace std;
namespace Jam2019
{
    extern void Problem1_1();
    extern void Problem1_2();
    extern void Problem1_3();
    extern void Problem1_4();
    extern void Problem1_5();
    extern void Problem1_6();
};
namespace Jam2018
{
    extern void Problem1_1();
    extern void Problem1_2();
    extern void Problem1_3();
    extern void Problem1_4();
    extern void Problem1_5();
    extern void Problem2_1();
    extern void Problem2_2();
    extern void Problem2_3();
    extern void Problem2_4();
    extern void Problem2_5();

};

namespace Jam2017
{
    extern void Problem2_1();
    extern void Problem2_2();
    extern void Problem2_3();
    extern void Problem2_4();
    extern void Problem2_5();
};

namespace Jam2016
{
    extern void Problem2_1();
    extern void Problem2_2();
    extern void Problem2_3();
    extern void Problem2_4();
    extern void Problem2_5();
};

namespace Algothirm
{
    extern void Test_Dijkstra();
    extern void Test_Euler();
    extern void Test_FordFulkerson();
    extern void Test_MaximumBipartiteMatching();
    extern void Test_Hamilton_Cycle();
}

#define uint64 unsigned long long
uint64 Fn(uint64 n)
{
    uint64 t0 = 0, t1 = 1;
    uint64 nextTerm = 0;
    if (n <= 0) nextTerm = 0;
    if (n == 1) nextTerm = 1;
    for (uint64 i = 2; i <= n; i++)
    {

        nextTerm = t0 + t1;
        t0 = t1;
        t1 = nextTerm;
    }

    return nextTerm;
}


int main(int argn, char* argv[])
{
   // uint64 result = Fn(10);
    //cout << result << endl;

    //Jam2016::Problem2_1();
    //Jam2016::Problem2_2();
    Jam2016::Problem2_3();

    //Jam2017::Problem2_2();
    //Jam2017::Problem2_4();

    //Jam2018::Problem1_1();
    //Jam2018::Problem1_2();
    //Jam2018::Problem1_3();
    //Jam2018::Problem1_4();
    //Jam2018::Problem1_5();
    //Jam2018::Problem2_1();
    //Jam2018::Problem2_2();
    //Jam2018::Problem2_3();
	//Jam2018::Problem2_4();
    //Jam2018::Problem2_5();

    //Jam2019::Problem1_1();
    //Jam2019::Problem1_2();
    //Jam2019::Problem1_3();
    //Jam2019::Problem1_4();
    //Jam2019::Problem1_5();
    //Jam2019::Problem1_6();

    //Algothirm::Test_Dijkstra();
    //Algothirm::Test_Euler();
    //Algothirm::Test_FordFulkerson();
    //Algothirm::Test_Hamilton_Cycle();
    getchar();
    while (true)
    {

    }

    return 0;
}

