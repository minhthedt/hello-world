#include "test_mutex.h"
#include <atomic>         // std::atomic, std::atomic_flag, ATOMIC_FLAG_INIT
#include <thread>         // std::thread, std::this_thread::yield
#include <mutex>

#include <chrono>
#include <vector>         // std::vector
#include <iostream>       // std::cout

namespace test_mutex_
{
    #define USE_MUTEX 1

    #if USE_MUTEX
    signed long long x = 0;
    std::mutex mtx;           // mutex for critical section
    #else
    signed long long x = 0;
    #endif

    #define NUMBER_LOOP 1000000

    void add()
    {
        for (int i = 0; i < NUMBER_LOOP; i++)
        {
            mtx.lock();
            x++;
            mtx.unlock();
        };

    }
    void sub()
    {
        for (int i = 0; i < NUMBER_LOOP; i++)
        {
            mtx.lock();
            x--;
            mtx.unlock();
        };
    }

    void main()
    {
        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
        std::vector<std::thread> theads;
        for (int i = 0; i < 10; i++)
        {
            theads.push_back(std::thread(add));
            theads.push_back(std::thread(sub));
        }


        for (int i = 0; i < theads.size(); i++)
        {
            theads[i].join();
        }

        signed long long a = x;
        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    #if USE_MUTEX
        printf("USE_MUTEX: x = %lld\n", a);
        std::cout << "elapsed time " << time_span.count() << " seconds." << std::endl;
    #else
        printf("don't USE_MUTEX: x = %lld\n", a);
        std::cout << "elapsed time " << time_span.count() << " seconds." << std::endl;
    #endif
    }

}

void test_mutex()
{
    test_mutex_::main();
}